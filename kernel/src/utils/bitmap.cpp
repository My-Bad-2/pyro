#include <utils/bitmap.hpp>

namespace utils {
/// \brief Constructor for the Bitmap class.
///
/// Constructs a Bitmap object with the specified base address and size.
///
/// \param base A pointer to the base address of the bitmap.
/// \param size The size of the bitmap in bits.
bitmap::bitmap(uint64_t* base, size_t size) {
    size_t word_size = calculate_word_size(size);

    // Check for a null pointer to avoid potential issues
    if (data == nullptr) {
        return;
    }

    this->data = base;
    this->size_in_bits = size;

    // Clear the bitmap initially
    for (size_t i = 0; i < word_size; ++i) {
        this->data[i] = 0;
    }
}

/// \brief Sets the value of the bit at the specified index to 1.
///
/// \param index The index of the bit to set.
void bitmap::set(size_t index) {
    // Check for out-of-bounds index
    if (index >= this->size_in_bits) {
        return;
    }

    size_t word_index = index / BLOCK_BITS;
    size_t bit_index = index % BLOCK_BITS;

    this->data[word_index] |= (1ULL << bit_index);
}

/// \brief Clears the value of the bit at the specified index to 0.
///
/// \param index The index of the bit to clear.
void bitmap::clear(size_t index) {
    // Check for out-of-bounds index
    if (index >= this->size_in_bits) {
        return;
    }

    size_t word_index = index / BLOCK_BITS;
    size_t bit_index = index % BLOCK_BITS;

    this->data[word_index] &= ~(1ULL << bit_index);
}

/// \brief Retrieves the value of the bit at the specified index.
///
/// \param index The index of the bit to retrieve.
/// \return The value of the bit at the specified index (0 or 1), or -1 for an out-of-bounds index.
int bitmap::get(size_t index) {
    // Check for out-of-bounds index
    if (index >= this->size_in_bits) {
        return -1;
    }

    size_t word_index = index / BLOCK_BITS;
    size_t bit_index = index % BLOCK_BITS;

    return (this->data[word_index] >> bit_index) & 1;
}

/// \brief Finds the index of the first unset bit in the bitmap.
///
/// This function searches for the first unset (0) bit in the bitmap and returns its index.
/// If all bits are set, it returns an empty optional.
///
/// \return An optional containing the index of the first unset bit, or an empty optional if all bits are set.
std::optional<size_t> bitmap::find_first_unset() {
    size_t word_size = calculate_word_size(this->size_in_bits);

    for (size_t i = 0; i < word_size; ++i) {
        if (this->data[i] != UINT64_MAX) {
            uint64_t mask = 1ULL;

            for (size_t j = 0; j < BLOCK_BITS; ++j) {
                if ((this->data[i] & mask) == 0) {
                    // Found an unset bit, return its index
                    return i * BLOCK_BITS + j;
                }

                mask <<= 1;
            }
        }
    }

    // No unset bits found
    return std::nullopt;
}

/// \brief Finds the index of the first set bit in the bitmap.
///
/// This function searches for the first set (1) bit in the bitmap and returns its index.
/// If all bits are unset, it returns an empty optional.
///
/// \return An optional containing the index of the first set bit, or an empty optional if all bits are unset.
std::optional<size_t> bitmap::find_first_set() {
    size_t word_size = calculate_word_size(size_in_bits);

    for (size_t i = 0; i < word_size; ++i) {
        if (this->data[i] != 0) {
            uint64_t mask = 1ULL;

            for (size_t j = 0; j < BLOCK_BITS; ++j) {
                if ((data[i] & mask) != 0) {
                    // Found a set bit, return its index
                    return i * BLOCK_BITS + j;
                }

                mask <<= 1;
            }
        }
    }

    // No set bits found
    return std::nullopt;
}

/// \brief Checks if the bit at the specified index is set (1).
///
/// \param index The index of the bit to check.
/// \return True if the bit is set, false otherwise.
bool bitmap::is_set(size_t index) {
    // Check for out-of-bounds index
    if (index >= size_in_bits) {
        // You might want to handle this case differently, e.g., throw an exception
        return false;
    }

    size_t word_index = index / BLOCK_BITS;
    size_t bit_index = index % BLOCK_BITS;

    // Check if the bit is set
    return (data[word_index] & (1ULL << bit_index)) != 0;
}

/// \brief Calculates the number of uint64_t words needed to represent a given number of bits.
///
/// This private method calculates the number of uint64_t words required to represent
/// a specified number of bits, considering the size of a block (BLOCK_BITS).
///
/// \param size_in_bits The total number of bits.
/// \return The number of uint64_t words required to represent the specified number of bits.
size_t bitmap::calculate_word_size(size_t size_in_bits) {
    return (size_in_bits + BLOCK_BITS - 1) / BLOCK_BITS;
}

}  // namespace utils