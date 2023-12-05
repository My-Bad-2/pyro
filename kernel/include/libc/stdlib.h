#ifndef KERNEL_INCLUDE_LIBC_STDLIB_H_
#define KERNEL_INCLUDE_LIBC_STDLIB_H_

#include <stddef.h>
#include <stdint.h>
#include <system/compiler.h>

__BEGIN_CDECLS

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

div_t div(int x, int y);
ldiv_t ldiv(long x, long y);
lldiv_t lldiv(long long x, long long y);

int abs(int j);
long labs(long j);
long long llabs(long long j);

int atoi(const char* nptr);
long atol(const char* nptr);
long long atoll(const char* nptr);

long strtol(const char* __restrict nptr, char** __restrict endptr, int base);
long long strtoll(const char* __restrict nptr, char** __restrict endptr, int base);

unsigned long strtoul(const char* __restrict nptr, char** __restrict endptr, int base);
unsigned long long strtoull(const char* __restrict nptr, char** __restrict endptr, int base);

__END_CDECLS

#endif // KERNEL_INCLUDE_LIBC_STDLIB_H_
