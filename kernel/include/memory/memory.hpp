#ifndef KERNEL_INCLUDE_MEMORY_MEMORY_HPP_
#define KERNEL_INCLUDE_MEMORY_MEMORY_HPP_

#include <stddef.h>
#include <stdint.h>

namespace memory {
/// \enum page_size_shift
/// \brief Enum representing different page size shifts.
enum page_size_shift : size_t {
    KiB4 = 12, ///< 4 KiB page size shift.
    MiB2 = 21, ///< 2 MiB page size shift.
    GiB1 = 30, ///< 1 GiB page size shift.
};

/// \brief Get the page size based on the given shift.
/// \param shift The page size shift (enumeration value).
/// \return The page size calculated using the shift.
constexpr inline size_t get_page_size(page_size_shift shift) {
    return (1 << static_cast<size_t>(shift));
}

/// \brief Convert bytes to kilobytes.
///
/// This constexpr function takes a size_t value representing the amount of memory
/// in bytes and returns the equivalent value in kilobytes using the formula:
/// \[ \text{kilobytes} = \frac{\text{mem}}{1000} \]
///
/// \param mem Amount of memory in bytes to be converted to kilobytes.
/// \return Equivalent value in kilobytes.
constexpr inline size_t bytes_to_kb(size_t mem) {
    return mem / 1000;
}

/// \brief Convert bytes to megabytes.
///
/// This constexpr function takes a size_t value representing the amount of memory
/// in bytes and returns the equivalent value in megabytes using the formula:
/// \[ \text{megabytes} = \frac{\text{mem}}{1000 \times 1000} \]
///
/// \param mem Amount of memory in bytes to be converted to megabytes.
/// \return Equivalent value in megabytes.
constexpr inline size_t bytes_to_mb(size_t mem) {
    return mem / (1000 * 1000);
}

/// \brief Convert bytes to gigabytes.
///
/// This constexpr function takes a size_t value representing the amount of memory
/// in bytes and returns the equivalent value in gigabytes using the formula:
/// \[ \text{gigabytes} = \frac{\text{mem}}{1000 \times 1000 \times 1000} \]
///
/// \param mem Amount of memory in bytes to be converted to gigabytes.
/// \return Equivalent value in gigabytes.
constexpr inline size_t bytes_to_gb(size_t mem) {
    return mem / (1000 * 1000 * 1000);
}
}  // namespace memory

#endif  // KERNEL_INCLUDE_MEMORY_MEMORY_HPP_