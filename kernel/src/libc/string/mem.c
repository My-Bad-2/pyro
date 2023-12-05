#include <limits.h>
#include <string.h>

typedef int word;

#define wsize sizeof(word)
#define wmask (wsize - 1)

/**
 * @brief Copies `count` bytes from the object pointed to by `src` to the object pointed to by `dest`. Both objects
 *  are reinterpreted as arrays of `unsigned char`.
 *
 *  If the objects overlap, the behavior is undefined.
 *  
 *  If either `dest` or `src` is an invalid or null pointer, the behavior is undefined, even if `count` is zero.
 *  
 *  If the objects are potentially-overlapping or not TriviallyCopyable, the behavior of memcpy is not specified
 *  and may be undefined.
 * 
 * @param dest pointer to the memory location to copy to
 * @param src pointer to the memory location to copy from
 * @param count number of bytes to copy
 * @return void* dest
 */
void* memcpy(void* __restrict dest, const void* __restrict src, size_t count) {
    char* _dest = (char*)(dest);
    const char* _src = (const char*)(src);
    size_t t;

    if (count == 0 || _dest == _src) {
        return dest;
    }

    if ((unsigned long)(_dest) < (unsigned long)(_src)) {
        // copy forward
        t = (unsigned long)(_src);  // only need the low bits

        if ((t | (unsigned long)(_dest)) & wmask) {
            // Try to align operands. This can't be done
            // unless the low bits match
            if ((t ^ (unsigned long)(_dest)) & wmask || count < wsize) {
                t = count;
            } else {
                t = wsize - (t & wmask);
            }

            count -= t;

            do {
                *_dest++ = *_src++;
            } while (--t);
        }

        // Copy whole words, then mop up any trailing bytes.
        t = count / wsize;

        if (t) {
            do {
                *(word*)(_dest) = *(word*)(_src);
                _src += wsize;
                _dest += wsize;
            } while (--t);
        }

        t = count & wmask;

        if (t) {
            do {
                *_dest++ = *_src++;
            } while (--t);
        }
    } else {
        // Copy backwards. Otherwise essentially the same.
        // Alignment works as before, except that it takes
        // (t & wmask) bytes to align, not wsize-(t & wmask).
        _src += count;
        _dest += count;

        t = (unsigned long)(src);

        if ((t | (unsigned long)(_dest)) & wmask) {
            if ((t ^ (unsigned long)(_dest)) & wmask || count <= wsize) {
                t = count;
            } else {
                t &= wmask;
            }

            count -= t;

            do {
                *--_dest = *--_src;
            } while (--t);
        }

        t = count / wsize;

        if (t) {
            do {
                _src -= wsize;
                _dest -= wsize;

                *(word*)_dest = *(word*)_src;
            } while (--t);
        }

        t = count & wmask;

        if (t) {
            do {
                *--_dest = *--_src;
            } while (--t);
        }
    }

    return dest;
}

/**
 * @brief Copies `count` characters from the object pointed to by `src` to the
 *  object pointed to by `dest`. Both objects are reinterpreted as arrays of `unsigned char`.
 *
 *  The objects may overlap: copying takes place as if the characters were copied to a temporary
 *  character array and then the characters were copied from the array to `dest`.
 *
 *  If either `dest` or `src` is an invalid or null pointer, the behavior is undefined, even if `count` is zero.
 *
 *  If the objects are potentially-overlapping or not TriviallyCopyable, the behavior of 
 *  `memmove` is not specified and may be undefined.
 * 
 * @param dest pointer to the memory location to copy to
 * @param src pointer to the memory location to copy from
 * @param count number of bytes to copy
 * @return void* dest
 */
void* memmove(void* dest, const void* src, size_t count) {
    const unsigned char* from = (const unsigned char*)(src);
    unsigned char* to = (unsigned char*)(dest);

    if (from == to || count == 0) {
        return dest;
    }

    if (to > from && to - from < (int)(count)) {
        // to overlaps with from
        // <from....>
        //     <to....>
        // copy in reverse, to avoid overwriting from
        for (size_t i = count - 1; i >= 0; i--) {
            to[i] = from[i];
        }

        return dest;
    }

    if (from > to && from - to < (int)(count)) {
        // to overlaps with from
        //    <from....>
        // <to....>
        // copy in reverse, to avoid overwriting from
        for (size_t i = 0; i < count; i++) {
            to[i] = from[i];
        }

        return dest;
    }

    memcpy(dest, src, count);

    return dest;
}

/**
 * @brief Copies the value `(unsigned char)(ch)` into each of the first `count` characters
 *  of the object pointed to by dest. If the object is a potentially-overlapping subobject
 *  or is not TriviallyCopyable (e.g., scalar, C-compatible struct, or an array of trivially
 *  copyable type), the behavior is undefined. If `count` is greater than the size of the 
 *  object pointed to by `dest`, the behavior is undefined.
 * 
 * @param dest pointer to the object to fill
 * @param ch fill byte
 * @param count number of bytes to fill
 * @return void* dest
 */
void* memset(void* dest, int ch, size_t count) {
    unsigned char* ptr = (unsigned char*)(dest);

    while (count-- > 0) {
        *ptr = ch;
    }

    return dest;
}

/**
 * @brief Reinterprets the objects pointed to by `lhs` and `rhs` as arrays of
 *  `unsigned char` and compares the first `count` bytes of these arrays. The
 *  comparison is done lexicographically.
 *  
 *  The sign of the result is the sign of the difference between the values of
 *  the first pair of bytes (both interpreted as `unsigned char`) that differ
 *  in the objects being compared.
 * 
 * @param lhs pointer to the memory buffers to compare
 * @param rhs pointer to the memory buffers to compare
 * @param count number of bytes to examine
 * @return int Negative value if the first differing byte (reinterpreted as `unsigned char`) in `lhs`
 *  is less than the corresponding byte in `rhs`.
 *  ​0​ if all count bytes of `lhs` and `rhs` are equal.
 *  Positive value if the first differing byte in lhs is greater than the corresponding byte in rhs.
 */
int memcmp(const void* lhs, const void* rhs, size_t count) {
    if (count == 0) {
        return 0;
    }

    const unsigned char* str1 = (const unsigned char*)(lhs);
    const unsigned char* str2 = (const unsigned char*)(rhs);

    while (--count && *str1++ == *str2++)
        ;

    return str1 - str2;
}

/**
 * @brief Converts `ch` to `unsigned char` and locates the first occurrence of that
 *  value in the initial count bytes (each interpreted as `unsigned char`) of the
 *  object pointed to by `ptr`.
 * 
 * @param src pointer to the object to be examined
 * @param ch byte to search for
 * @param length max number of bytes to examine
 * @return void* pointer to the location of the byte, or a null pointer if no such byte is found.
 */
void* memchr(const void* src, int ch, size_t length) {
    const char* big = (const char*)(src);

    for (size_t n = 0; n < length; n++) {
        if (big[n] == ch) {
            return (void*)&big[n];
        }
    }

    return NULL;
}
