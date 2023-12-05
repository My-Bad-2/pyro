#ifndef KERNEL_INCLUDE_LIBC_STRING_H_
#define KERNEL_INCLUDE_LIBC_STRING_H_

#include <stddef.h>
#include <stdint.h>
#include <system/compiler.h>

__BEGIN_CDECLS

void* memcpy(void* __restrict dest, const void* __restrict src, size_t count);
void* memmove(void* dest, const void* src, size_t count);
void* memset(void* dest, int ch, size_t count);
int memcmp(const void* lhs, const void* rhs, size_t count);
void* memchr(const void* src, int ch, size_t count);

char* strcpy(char* __restrict dest, const char* __restrict src);
char* strncpy(char* __restrict dest, const char* __restrict src, size_t count);

char* strcat(char* __restrict dest, const char* __restrict src);
char* strncat(char* __restrict dest, const char* __restrict src, size_t count);

int strcmp(const char* lhs, const char* rhs);
int strncmp(const char* lhs, const char* rhs, size_t count);

char* strchr(const char* str, int ch);
char* strrchr(const char* str, int ch);

size_t strcspn(const char* dest, const char* src);
size_t strspn(const char* dest, const char* src);
char* strpbrk(const char* dest, const char* breakset);
char* strstr(const char* haystack, const char* needle);
char* strtok(char* __restrict str, const char* __restrict delim);

size_t strlen(const char* str);

__END_CDECLS

#endif
