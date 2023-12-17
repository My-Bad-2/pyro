#ifndef KERNEL_INCLUDE_UTILS_MISC_HPP_
#define KERNEL_INCLUDE_UTILS_MISC_HPP_

#include <boot/bootinfo.h>
#include <utils/common.h>
#include <concepts>

namespace utils {
/// \brief Offset for higher half of the virtual address space.
extern uintptr_t hhdm_offset;

/// \brief Initializes the memory utilities with the provided boot information.
/// \param bootinfo The boot information structure.
void initialize(bootinfo_t* bootinfo);

/// \brief Checks if the given address is in the higher half of the virtual address space.
/// \param address The address to check.
/// \return True if the address is in the higher half, false otherwise.
inline constexpr bool is_higher_half(auto address) {
    return (uintptr_t)address >= hhdm_offset;
}

/// \brief Converts the given address to the higher half of the virtual address space if needed.
/// \tparam T The type of the input address.
/// \tparam Ret The type of the returned address, deduced based on T.
/// \param address The address to convert.
/// \return The converted address.
template <
    typename T,
    typename Ret = std::conditional_t<
        std::integral<T>,
        std::conditional_t<std::unsigned_integral<T>, uintptr_t, uintptr_t>, T>>
inline constexpr Ret to_higher_half(T address) {
    return is_higher_half(address) ? Ret(address)
                                   : Ret(uintptr_t(address) + hhdm_offset);
}

/// \brief Converts the given address from the higher half of the virtual address space if needed.
/// \tparam T The type of the input address.
/// \tparam Ret The type of the returned address, deduced based on T.
/// \param address The address to convert.
/// \return The converted address.
template <
    typename T,
    typename Ret = std::conditional_t<
        std::integral<T>,
        std::conditional_t<std::unsigned_integral<T>, uintptr_t, uintptr_t>, T>>
inline constexpr Ret from_higher_half(T address) {
    return !is_higher_half(address) ? Ret(address)
                                    : Ret(uintptr_t(address) - hhdm_offset);
}

/// \brief Aligns the given integral value down to the nearest multiple of another integral value.
/// \param p1 The value to align.
/// \param p2 The alignment value.
/// \return The aligned value.
inline constexpr auto align_down(std::integral auto p1, std::integral auto p2) {
    return (p1 & ~(p2 - 1));
}

/// \brief Aligns the given integral value up to the nearest multiple of another integral value.
/// \param p1 The value to align.
/// \param p2 The alignment value.
/// \return The aligned value.
inline constexpr auto align_up(std::integral auto p1, std::integral auto p2) {
    return align_down(p1 + p2 - 1, p2);
}

/// \brief Calculates the rounded-up division of two integral values.
/// \param p1 The dividend.
/// \param p2 The divisor.
/// \return The rounded-up division result.
inline constexpr auto div_roundup(std::integral auto p1,
                                  std::integral auto p2) {
    return align_up(p1, p2) / p2;
}
}  // namespace utils

#endif  // KERNEL_INCLUDE_UTILS_MISC_HPP_