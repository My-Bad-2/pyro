#ifndef KERNEL_INCLUDE_LIBC_STRING_H_
#define KERNEL_INCLUDE_LIBC_STRING_H_

#include <stddef.h>
#include <stdint.h>
#include <system/compiler.h>

__BEGIN_CDECLS

/// \brief Copies a block of memory from a source address to a destination address.
/// \param dest The destination address.
/// \param src The source address.
/// \param count The number of bytes to copy.
/// \return A pointer to the destination address.
void* memcpy(void* __restrict dest, const void* __restrict src, size_t count);

/// \brief Copies a block of memory, handling overlapping regions.
/// \param dest The destination address.
/// \param src The source address.
/// \param count The number of bytes to copy.
/// \return A pointer to the destination address.
void* memmove(void* dest, const void* src, size_t count);

/// \brief Fills a block of memory with a specified value.
/// \param dest The destination address.
/// \param ch The value to be set.
/// \param count The number of bytes to set.
/// \return A pointer to the destination address.
void* memset(void* dest, int ch, size_t count);

/// \brief Compares two blocks of memory.
/// \param lhs The first block of memory.
/// \param rhs The second block of memory.
/// \param count The number of bytes to compare.
/// \return An integer less than, equal to, or greater than 0 if lhs is found, respectively, to be less than, to match,
/// or be greater than rhs.
int memcmp(const void* lhs, const void* rhs, size_t count);

/// \brief Searches for a character in a block of memory.
/// \param src The block of memory to search.
/// \param ch The character to search for.
/// \param count The number of bytes to search.
/// \return A pointer to the first occurrence of the character, or NULL if not found.
void* memchr(const void* src, int ch, size_t count);

/// \brief Copies a string from source to destination.
/// \param dest The destination string.
/// \param src The source string.
/// \return A pointer to the destination string.
char* strcpy(char* __restrict dest, const char* __restrict src);

/// \brief Copies a specified number of characters from source to destination.
/// \param dest The destination string.
/// \param src The source string.
/// \param count The number of characters to copy.
/// \return A pointer to the destination string.
char* strncpy(char* __restrict dest, const char* __restrict src, size_t count);

/// \brief Concatenates two strings.
/// \param dest The destination string.
/// \param src The source string.
/// \return A pointer to the destination string.
char* strcat(char* __restrict dest, const char* __restrict src);

/// \brief Concatenates a specified number of characters from the source to the destination.
/// \param dest The destination string.
/// \param src The source string.
/// \param count The number of characters to concatenate.
/// \return A pointer to the destination string.
char* strncat(char* __restrict dest, const char* __restrict src, size_t count);

/// \brief Compares two strings.
/// \param lhs The first string.
/// \param rhs The second string.
/// \return An integer less than, equal to, or greater than 0 if lhs is found, respectively, to be less than, to match,
/// or be greater than rhs.
int strcmp(const char* lhs, const char* rhs);

/// \brief Compares a specified number of characters from two strings.
/// \param lhs The first string.
/// \param rhs The second string.
/// \param count The number of characters to compare.
/// \return An integer less than, equal to, or greater than 0 if lhs is found, respectively, to be less than, to match,
/// or be greater than rhs.
int strncmp(const char* lhs, const char* rhs, size_t count);

/// \brief Finds the first occurrence of a character in a string.
/// \param str The string to search.
/// \param ch The character to find.
/// \return A pointer to the first occurrence of the character, or NULL if not found.
char* strchr(const char* str, int ch);

/// \brief Finds the last occurrence of a character in a string.
/// \param str The string to search.
/// \param ch The character to find.
/// \return A pointer to the last occurrence of the character, or NULL if not found.
char* strrchr(const char* str, int ch);

/// \brief Calculates the length of the initial substring of dest consisting of characters not in src.
/// \param dest The string to search.
/// \param src The set of characters to avoid.
/// \return The length of the initial substring of dest consisting of characters not in src.
size_t strcspn(const char* dest, const char* src);

/// \brief Calculates the length of the initial substring of dest consisting of characters in src.
/// \param dest The string to search.
/// \param src The set of characters to include.
/// \return The length of the initial substring of dest consisting of characters in src.
size_t strspn(const char* dest, const char* src);

/// \brief Finds the first occurrence of any character in a set within a string.
/// \param dest The string to search.
/// \param breakset The set of characters to search for.
/// \return A pointer to the first occurrence of any character in breakset, or NULL if not found.
char* strpbrk(const char* dest, const char* breakset);

/// \brief Finds the first occurrence of a substring within a string.
/// \param haystack The string to search.
/// \param needle The substring to find.
/// \return A pointer to the first occurrence of the substring, or NULL if not found.
char* strstr(const char* haystack, const char* needle);

/// \brief Breaks a string into a series of tokens.
/// \param str The string to tokenize.
/// \param delim The set of delimiter characters.
/// \return A pointer to the first token found in the string, or NULL if no tokens are found.
char* strtok(char* __restrict str, const char* __restrict delim);

/// \brief Calculates the length of a string.
/// \param str The string to measure.
/// \return The length of the string.
size_t strlen(const char* str);

__END_CDECLS

#endif
