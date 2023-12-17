#ifndef KERNEL_INCLUDE_UTILS_BITMAP_HPP_
#define KERNEL_INCLUDE_UTILS_BITMAP_HPP_

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <utils/common.h>

namespace utils {
/// \tparam T The type of elements stored in the bitmap.
template <typename T>
class bitmap {
   public:
    /// \brief Default constructor.
    constexpr bitmap() = default;

    /// \brief Parameterized constructor.
    ///
    /// \param buffer Pointer to the buffer storing the bitmap data.
    /// \param size Size of the buffer in terms of elements of type T.
    constexpr bitmap(T* buffer, size_t size)
        : buffer_(buffer), size_(size), initialized_(true) {}

    /// \brief Destructor.
    constexpr ~bitmap() {}

    /// \brief Initialize the bitmap with a buffer and size.
    ///
    /// \param buffer Pointer to the buffer storing the bitmap data.
    /// \param size Size of the buffer in terms of elements of type T.
    void initialize(T* buffer, size_t size) {
        assert(!this->initialized_);

        this->buffer_ = buffer;
        this->size_ = size;

        this->initialized_ = true;
    }

    /// \brief Nested bit structure representing a single bit in the bitmap.
    struct bit {
        bitmap& parent;  ///< Reference to the parent bitmap.
        size_t index;    ///< Index of the bit within the bitmap.

        /// \brief Constructor for the bit structure.
        ///
        /// \param parent Reference to the parent bitmap.
        /// \param index Index of the bit within the bitmap.
        constexpr bit(bitmap& parent, size_t index)
            : parent(parent), index(index) {}

        /// \brief Assignment operator for setting the value of the bit.
        ///
        /// \param value The value to be assigned to the bit.
        constexpr void operator=(bool value) {
            this->parent.set(this->index, value);
        }

        /// \brief Conversion operator to bool for retrieving the value of the bit.
        ///
        /// \return The value of the bit.
        constexpr operator bool() const {
            return this->parent.get(this->index);
        }
    };

    /// \brief Overloaded subscript operator for accessing bits in the bitmap.
    ///
    /// \param index Index of the bit to be accessed.
    /// \return Bit reference for the specified index.
    constexpr bit operator[](size_t index) {
        assert(this->initialized_);
        return bit(*this, index);
    }

    /// \brief Get the value of a specific bit in the bitmap.
    ///
    /// \param index Index of the bit to be retrieved.
    /// \return The value of the specified bit.
    constexpr bool get(size_t index) {
        assert(this->initialized_);
        return this->buffer_[index / bit_size()] & (1 << (index % bit_size()));
    }

    /// \brief Set the value of a specific bit in the bitmap.
    ///
    /// \param index Index of the bit to be set.
    /// \param value The value to be set for the specified bit.
    /// \return True if the operation was successful, false otherwise.
    constexpr bool set(size_t index, bool value) {
        assert(this->initialized_);

        if (index > size_ * bit_size()) {
            return false;
        }

        if (value) {
            this->buffer_[index / bit_size()] |= (1 << (index % bit_size()));
        } else {
            this->buffer_[index / bit_size()] &= ~(1 << (index % bit_size()));
        }

        return true;
    }

    /// \brief Get the length of the bitmap.
    ///
    /// \return The length of the bitmap in terms of elements of type T.
    constexpr size_t length() const { return this->initialized_ ? size_ : 0; }

    /// \brief Get a pointer to the underlying buffer of the bitmap.
    ///
    /// \return Pointer to the buffer storing the bitmap data.
    constexpr T* data() const { return this->buffer_; }

    /// \brief Check if the bitmap is initialized.
    ///
    /// \return True if the bitmap is initialized, false otherwise.
    constexpr bool initialized() const { return this->initialized_; }

   private:
    /// \brief Get the size of a `T` in bits.
    ///
    /// \return The size of a `T` in bits.
    constexpr size_t bit_size() const { return sizeof(T) * 8; }

   private:
    // clang-format off
    bool initialized_ = false;  ///< Flag indicating whether the bitmap is initialized.
    // clang-format on

    T* buffer_ = nullptr;  ///< Pointer to the buffer storing the bitmap data.
    size_t size_ = 0;  ///< Size of the buffer in terms of elements of type T.
};
}  // namespace utils

#endif  // KERNEL_INCLUDE_UTILS_BITMAP_HPP_