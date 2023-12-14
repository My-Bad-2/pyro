#ifndef KERNEL_INCLUDE_UTILS_MUTEX_HPP_
#define KERNEL_INCLUDE_UTILS_MUTEX_HPP_

#include <stddef.h>
#include <utils/common.h>
#include <atomic>

UTILS_NAMESPACE_BEGIN

/// \struct ticket_spinlock
/// \brief A simple ticket-based spinlock implementation.
struct ticket_spinlock {
    /// \brief Default constructor.
    ///
    /// Initializes the next and serving tickets.
    constexpr ticket_spinlock() : next_ticket_(0), serving_ticket_(0) {}

    /// \brief Copy constructor (deleted).
    ticket_spinlock(const ticket_spinlock&) = delete;

    /// \brief Copy assignment operator (deleted).
    ticket_spinlock& operator=(const ticket_spinlock&) = delete;

    /// \brief Acquires the lock.
    void lock();

    /// \brief Checks if the lock is currently held.
    bool is_locked();

    /// \brief Releases the lock.
    void unlock();

   private:
    std::atomic<size_t> next_ticket_;  ///< Atomic counter for the next ticket.
    // clang-format off
    std::atomic<size_t> serving_ticket_;  ///< Atomic counter for the serving ticket.
    // clang-format on
};

/// \struct irq_lock
/// \brief A struct that provides a lock for interrupt status.
struct irq_lock {
   public:
    /// \brief Default constructor.
    ///
    /// Initializes the interrupt status to false and the internal ticket_spinlock.
    constexpr irq_lock() : irqs_(false), lock_() {}

    /// \brief Copy constructor (deleted).
    irq_lock(const irq_lock&) = delete;

    /// \brief Copy assignment operator (deleted).
    irq_lock& operator=(const irq_lock&) = delete;

    /// \brief Acquires the lock, disabling interrupts.
    void lock();

    /// \brief Releases the lock, restoring the previous interrupt status.
    void unlock();

    /// \brief Checks if the lock is currently held.
    ///
    /// \return true if the lock is held, false otherwise.
    bool is_locked();

   private:
    bool irqs_;             ///< Current interrupt status.
    ticket_spinlock lock_;  ///< Internal ticket_spinlock for managing the lock.
};

/// \tparam MutexType The type of the mutex to be used with the scoped lock.
template <typename MutexType>
class scoped_lock {
   public:
    /// \brief Alias for the mutex type.
    using mutex_type = MutexType;

    /// \brief Explicit constructor to acquire the lock on the specified mutex.
    explicit scoped_lock(mutex_type& mutex)
        : mutex_(__GET_ADDRESS(mutex)), locked_(true) {
        mutex.lock();
    }

    /// \brief Move constructor for scoped_lock.
    ///
    /// \param other The rvalue reference to another scoped_lock.
    scoped_lock(scoped_lock&& other) noexcept
        : mutex_(nullptr), locked_(false) {
        this->swap(other);
    }

    /// \brief Destructor.
    ///
    /// If the lock is held, unlocks the associated mutex.
    ~scoped_lock() {
        if (this->locked_) {
            this->mutex_->unlock();
        }
    }

    /// \brief Move assignment operator for scoped_lock.
    ///
    /// \param other The rvalue reference to another scoped_lock.
    ///
    /// If the current lock is held, unlocks the associated mutex before swapping.
    scoped_lock& operator=(scoped_lock&& other) {
        if (this->locked_) {
            this->unlock();
        }

        this->swap(other);
        return *this;
    }

    /// \brief Acquires the lock if not already held.
    void lock() {
        if (this->mutex_) {
            this->mutex_->lock();
            this->locked_ = true;
        }
    }

    /// \brief Releases the lock if held.
    void unlock() {
        if (this->mutex_) {
            this->mutex_->unlock();
            this->locked_ = false;
        }
    }

    /// \brief Releases ownership of the lock and returns a pointer to the associated mutex.
    ///
    /// The caller is responsible for managing the lifetime of the returned mutex.
    mutex_type* release() noexcept {
        mutex_type* ret = this->mutex_;

        this->mutex_ = nullptr;
        this->locked_ = false;

        return ret;
    }

    /// \brief Swaps the contents of two scoped_lock objects.
    void swap(scoped_lock& other) noexcept {
        using std::swap;

        swap(this->mutex_, other.mutex_);
        swap(this->locked_, other.locked_);
    }

    /// \brief Returns a pointer to the associated mutex.
    mutex_type* mutex() const noexcept { return this->mutex_; }

    /// \brief Checks if the lock is currently held.
    bool owns_lock() const noexcept { return this->locked_; }

    /// \brief Conversion to bool, indicating whether the lock is held.
    explicit operator bool() const noexcept { return this->owns_lock(); }

    /// \brief Friend function to swap two scoped_lock objects.
    friend void swap(scoped_lock& lhs, scoped_lock& rhs) noexcept {
        return lhs.swap(rhs);
    }

   private:
    MutexType* mutex_;  ///< Pointer to the associated mutex.
    bool locked_;       ///< Flag indicating whether the lock is held.
};

UTILS_NAMESPACE_END

#endif  // KERNEL_INCLUDE_UTILS_MUTEX_HPP_