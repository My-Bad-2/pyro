#include <arch/arch.h>
#include <utils/mutex.hpp>
#include "x86.h"

namespace utils {
/// \brief Acquires the lock.
///
/// Atomically increments the next ticket and spins until the serving ticket matches the acquired ticket.
void ticket_spinlock::lock() {
    // Increment and fetch the next ticket using relaxed memory order.
    size_t ticket = next_ticket_.fetch_add(1, std::memory_order_relaxed);

    // Spin until the serving ticket matches the acquired ticket.
    while (serving_ticket_.load(std::memory_order_acquire) != ticket) {
        // Use architecture-specific pause instruction to reduce contention in the spin loop.
        pause();
    }
}

/// \brief Checks if the lock is currently held.
///
/// \return true if the lock is held, false otherwise.
bool ticket_spinlock::is_locked() {
    // Check if the serving ticket incremented by 1 equals the next ticket.
    return (serving_ticket_.load(std::memory_order_relaxed) + 1) ==
           next_ticket_.load(std::memory_order_relaxed);
}

/// \brief Releases the lock.
///
/// If the lock is held, increments the serving ticket to release the lock.
void ticket_spinlock::unlock() {
    // Check if the lock is currently held.
    if (!this->is_locked()) {
        // If the lock is not held, do nothing and return.
        return;
    }

    // If the lock is held, increment the serving ticket to release the lock.
    size_t current = serving_ticket_.load(std::memory_order_relaxed);
    serving_ticket_.store(current + 1, std::memory_order_release);
}

/// \brief Locks interrupts and acquires the lock.
///
/// This function retrieves the current interrupt status, disables interrupts,
/// acquires the lock, and saves the original interrupt status to be restored
/// upon unlocking
void irq_lock::lock() {
    // Retrieve the current interrupt status
    bool irqs = interrupt_status();

    // Disable interrupts
    interrupt_disable();

    // Acquire the lock
    this->lock_.lock();

    // Save the original interrupt status to be restored upon unlocking
    this->irqs_ = irqs;
}

/// \brief Unlocks the lock and restores interrupt status.
///
/// This function releases the lock, restores the interrupt status to the value
/// saved during the locking, and enables or disables interrupts based on the
/// saved status.
void irq_lock::unlock() {
    // Retrieve the saved interrupt status
    bool irqs = this->irqs_;

    // Release the lock
    this->lock_.unlock();

    // Enable or disable interrupts based on the saved status
    if (irqs) {
        interrupt_enable();
    } else {
        interrupt_disable();
    }
}

/// \brief Checks if the lock is currently held.
///
/// \return True if the lock is held, false otherwise.
bool irq_lock::is_locked() {
    // Check if the lock is currently held
    return this->lock_.is_locked();
}
}  // namespace utils