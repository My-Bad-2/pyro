#include <limits.h>
#include <string.h>

typedef int word;

#define wsize sizeof(word)
#define wmask (wsize - 1)

/// \brief Copy memory from one location to another efficiently.
///
/// This function copies 'count' bytes of memory from the source 'src' to the
/// destination 'dest' efficiently, utilizing architecture-specific features.
///
/// \param dest  Pointer to the destination memory.
/// \param src   Pointer to the source memory.
/// \param count Number of bytes to copy.
///
/// \return A pointer to the destination memory 'dest'.
void* memcpy(void* __restrict dest, const void* __restrict src, size_t count) {
    // Cast pointers to uint8_t* for byte-wise manipulation
    uint8_t* _dest = (uint8_t*)dest;
    const uint8_t* _src = (const uint8_t*)src;

    // Check if pointers are aligned to copy in chunks of 8 bytes (64 bits)
    if (((uintptr_t)_dest % sizeof(uint64_t) == 0) &&
        ((uintptr_t)_src % sizeof(uint64_t) == 0) &&
        (count >= sizeof(uint64_t))) {
        // Copy in chunks of 64 bits (8 bytes) for efficiency
        while (count >= sizeof(uint64_t)) {
            *((uint64_t*)_dest) = *((const uint64_t*)_src);
            _src += sizeof(uint64_t);
            _dest += sizeof(uint64_t);
            count -= sizeof(uint64_t);
        }
    }

    // Check if there are remaining bytes to copy
    if (count > 0) {
        // Use word-wise copy for remaining bytes if possible
        if (((uintptr_t)_dest % sizeof(uint32_t) == 0) &&
            ((uintptr_t)_src % sizeof(uint32_t) == 0) &&
            (count >= sizeof(uint32_t))) {
            // Copy in chunks of 32 bits (4 bytes) for efficiency
            while (count >= sizeof(uint32_t)) {
                *((uint32_t*)_dest) = *((const uint32_t*)_src);
                _src += sizeof(uint32_t);
                _dest += sizeof(uint32_t);
                count -= sizeof(uint32_t);
            }
        }

        // Copy any remaining bytes individually
        while (count-- > 0) {
            *_dest++ = *_src++;
        }
    }

    // Return a pointer to the destination memory
    return dest;
}

/// \brief Copy memory from one location to another, handling overlapping regions.
///
/// This function copies 'count' bytes of memory from the source 'src' to the
/// destination 'dest'. The memory regions can overlap, and the copy is performed
/// in a way that ensures correct behavior in such cases.
///
/// \param dest  Pointer to the destination memory.
/// \param src   Pointer to the source memory.
/// \param count Number of bytes to copy.
///
/// \return A pointer to the destination memory 'dest'.
void* memmove(void* dest, const void* src, size_t count) {
    // Cast pointers to uint8_t* for byte-wise manipulation
    uint8_t* _dest = (uint8_t*)dest;
    const uint8_t* _src = (const uint8_t*)src;

    // Check if src and dest overlap and determine the direction of copy
    if (_src < _dest && _dest < _src + count) {
        // Copy from end to start using word-wise copy for optimization
        _src += count;
        _dest += count;

        // Check if pointers are aligned to copy in chunks of 8 bytes (64 bits)
        if (((uintptr_t)_dest % sizeof(uint64_t) == 0) &&
            ((uintptr_t)_src % sizeof(uint64_t) == 0)) {
            // Copy in chunks of 64 bits (8 bytes) for efficiency
            while (count >= sizeof(uint64_t)) {
                _src -= sizeof(uint64_t);
                _dest -= sizeof(uint64_t);
                *((uint64_t*)_dest) = *((const uint64_t*)_src);
                count -= sizeof(uint64_t);
            }
        }

        // Copy any remaining bytes individually
        while (count-- > 0) {
            *--_dest = *--_src;
        }
    } else {
        // Copy from start to end using word-wise copy for optimization
        // Check if pointers are aligned to copy in chunks of 8 bytes (64 bits)
        if (((uintptr_t)_dest % sizeof(uint64_t) == 0) &&
            ((uintptr_t)_src % sizeof(uint64_t) == 0)) {
            // Copy in chunks of 64 bits (8 bytes) for efficiency
            while (count >= sizeof(uint64_t)) {
                *((uint64_t*)_dest) = *((const uint64_t*)_src);
                _src += sizeof(uint64_t);
                _dest += sizeof(uint64_t);
                count -= sizeof(uint64_t);
            }
        }

        // Copy any remaining bytes individually
        while (count-- > 0) {
            *_dest++ = *_src++;
        }
    }

    // Return a pointer to the destination memory
    return dest;
}

/// \brief Set a block of memory to a specific value efficiently.
///
/// This function sets the first 'count' bytes of the memory block pointed to by
/// 'dest' to the specified 'value'.
///
/// \param dest  Pointer to the memory block to be set.
/// \param value The value to set in each byte.
/// \param count Number of bytes to set.
///
/// \return A pointer to the destination memory 'dest'.
void* memset(void* dest, int value, size_t count) {
    unsigned char* ptr = (unsigned char*)(dest);

    while (count-- > 0) {
        *ptr = value;
    }

    return dest;
}

/// \brief Compare two blocks of memory.
///
/// This function compares the first 'count' bytes of the memory blocks pointed
/// to by 'lhs' and 'rhs'. It returns an integer less than, equal to, or greater
/// than zero if the first differing byte (if any) is less than, equal to, or
/// greater than 'rhs'.
///
/// \param lhs   Pointer to the first memory block.
/// \param rhs   Pointer to the second memory block.
/// \param count Number of bytes to compare.
///
/// \return An integer less than, equal to, or greater than zero.
int memcmp(const void* lhs, const void* rhs, size_t count) {
    const unsigned char* p1 = (const unsigned char*)lhs;
    const unsigned char* p2 = (const unsigned char*)rhs;

    // Compare memory in chunks of 8 bytes for efficiency
    while (count >= sizeof(uint64_t)) {
        uint64_t val1 = *((const uint64_t*)p1);
        uint64_t val2 = *((const uint64_t*)p2);

        if (val1 != val2) {
            return (val1 < val2) ? -1 : 1;
        }

        p1 += sizeof(uint64_t);
        p2 += sizeof(uint64_t);
        count -= sizeof(uint64_t);
    }

    // Compare any remaining bytes individually
    while (count-- > 0) {
        if (*p1 != *p2) {
            return (*p1 < *p2) ? -1 : 1;
        }

        ++p1;
        ++p2;
    }

    // Memory blocks are equal
    return 0;
}

/// \brief Locate the last occurrence of a byte in a block of memory.
///
/// This function searches for the last occurrence of the byte 'ch' in the
/// memory block pointed to by 'src'. The search is performed backward from
/// the end of the block.
///
/// \param src Pointer to the memory block.
/// \param ch  The byte to search for.
/// \param n   Number of bytes in the memory block.
///
/// \return A pointer to the last occurrence of the byte, or NULL if not found.
void* memrchr(const void* src, int ch, size_t n) {
    const unsigned char* p = (const unsigned char*)src;

    // Move to the end of the block
    p += n;

    // Perform word-wise backward search for 'ch'
    while (n >= sizeof(uint64_t)) {
        p -= sizeof(uint64_t);
        uint64_t word = *((const uint64_t*)p);

        // Check if 'ch' is present in the current word
        if ((word & 0xFF) == (unsigned char)ch ||
            ((word >> 8) & 0xFF) == (unsigned char)ch ||
            ((word >> 16) & 0xFF) == (unsigned char)ch ||
            ((word >> 24) & 0xFF) == (unsigned char)ch ||
            ((word >> 32) & 0xFF) == (unsigned char)ch ||
            ((word >> 40) & 0xFF) == (unsigned char)ch ||
            ((word >> 48) & 0xFF) == (unsigned char)ch ||
            ((word >> 56) & 0xFF) == (unsigned char)ch) {
            return (void*)p;
        }

        n -= sizeof(uint64_t);
    }

    // Check any remaining bytes individually
    while (n-- > 0) {
        if (*--p == (unsigned char)ch) {
            return (void*)p;
        }
    }

    // Byte 'ch' not found in the memory block
    return NULL;
}
