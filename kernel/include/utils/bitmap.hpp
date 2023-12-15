#ifndef KERNEL_INCLUDE_UTILS_BITMAP_HPP_
#define KERNEL_INCLUDE_UTILS_BITMAP_HPP_

#include <stddef.h>
#include <stdint.h>
#include <utils/common.h>
#include <optional>

namespace utils {
/// \def BLOCK_BITS
/// \brief The number of bits in a block (size_t).
///
/// This constant represents the number of bits in a block of size_t.
constexpr size_t BLOCK_BITS = sizeof(size_t) * 8;

/// \brief Calculate the number of blocks required to represent a given number of bits.
///
/// This function calculates the number of blocks needed to represent a given number of bits.
/// The calculation takes into account the size of a block (BLOCK_BITS) and rounds up if necessary.
///
/// \param bits The total number of bits.
/// \return The number of blocks required to represent the specified number of bits.
constexpr size_t calculate_blocks(size_t bits) {
    /// \note The division is rounded up by adding 1 if there's a remainder.
    return (bits % BLOCK_BITS == 0) ? (bits / BLOCK_BITS)
                                    : (bits / BLOCK_BITS) + 1;
}

/// \class bitmap
/// \brief Represents a simple bitmap using uint64_t blocks.
///
/// The Bitmap class provides a basic implementation of a bitmap using uint64_t blocks.
class bitmap {
   public:
    /// \brief Constructor for the Bitmap class.
    ///
    /// Constructs a Bitmap object with the specified base address and size.
    ///
    /// \param base A pointer to the base address of the bitmap.
    /// \param size The size of the bitmap in bits.
    bitmap(uint64_t* base, size_t size);

    /// \brief Retrieves the value of the bit at the specified index.
    ///
    /// \param index The index of the bit to retrieve.
    /// \return The value of the bit at the specified index.
    int get(size_t index);

    /// \brief Sets the value of the bit at the specified index to 1.
    ///
    /// \param index The index of the bit to set.
    void set(size_t index);

    /// \brief Clears the value of the bit at the specified index to 0.
    ///
    /// \param index The index of the bit to clear.
    void clear(size_t index);

    /// \brief Finds the index of the first unset bit in the bitmap.
    ///
    /// This function searches for the first unset (0) bit in the bitmap and returns its index.
    /// If all bits are set, it returns an empty optional.
    ///
    /// \return An optional containing the index of the first unset bit, or an empty optional if all bits are set.
    std::optional<size_t> find_first_unset();

    /// \brief Finds the index of the first set bit in the bitmap.
    ///
    /// This function searches for the first set (1) bit in the bitmap and returns its index.
    /// If all bits are unset, it returns an empty optional.
    ///
    /// \return An optional containing the index of the first set bit, or an empty optional if all bits are unset.
    std::optional<size_t> find_first_set();

    /// \brief Checks if the bit at the specified index is set (1).
    ///
    /// \param index The index of the bit to check.
    /// \return True if the bit is set, false otherwise.
    bool is_set(size_t index);

   private:
    /// \brief Calculates the number of uint64_t words needed to represent a given number of bits.
    ///
    /// This private method calculates the number of uint64_t words required to represent
    /// a specified number of bits, considering the size of a block (BLOCK_BITS).
    ///
    /// \param size_in_bits The total number of bits.
    /// \return The number of uint64_t words required to represent the specified number of bits.
    size_t calculate_word_size(size_t size_in_bits);

   private:
    uint64_t* data;       ///< Pointer to the base address of the bitmap.
    size_t size_in_bits;  ///< The size of the bitmap in bits.
};
}  // namespace utils

#endif  // KERNEL_INCLUDE_UTILS_BITMAP_HPP_