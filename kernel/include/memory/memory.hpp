#ifndef KERNEL_INCLUDE_MEMORY_MEMORY_HPP_
#define KERNEL_INCLUDE_MEMORY_MEMORY_HPP_

#include <stddef.h>
#include <stdint.h>

namespace memory {
/// \brief Convert bytes to megabytes.
///
/// This constexpr function takes a size_t value representing the amount of memory
/// in bytes and returns the equivalent value in megabytes using the formula:
/// \[ \text{megabytes} = \frac{\text{mem}}{1024 \times 1024} \]
///
/// \param mem Amount of memory in bytes to be converted to megabytes.
/// \return Equivalent value in megabytes.
constexpr size_t bytes_to_mb(size_t mem) {
    return mem / (1024 * 1024);
}

/// \brief Convert bytes to kilobytes.
///
/// This constexpr function takes a size_t value representing the amount of memory
/// in bytes and returns the equivalent value in kilobytes using the formula:
/// \[ \text{kilobytes} = \frac{\text{mem}}{1024} \]
///
/// \param mem Amount of memory in bytes to be converted to kilobytes.
/// \return Equivalent value in kilobytes.
constexpr size_t bytes_to_kb(size_t mem) {
    return mem / 1024;
}

/// \brief Convert bytes to gigabytes.
///
/// This constexpr function takes a size_t value representing the amount of memory
/// in bytes and returns the equivalent value in gigabytes using the formula:
/// \[ \text{gigabytes} = \frac{\text{mem}}{1024 \times 1024 \times 1024} \]
///
/// \param mem Amount of memory in bytes to be converted to gigabytes.
/// \return Equivalent value in gigabytes.
constexpr size_t bytes_to_gb(size_t mem) {
    return mem / (1024 * 1024 * 1024);
}
}  // namespace memory

#endif  // KERNEL_INCLUDE_MEMORY_MEMORY_HPP_