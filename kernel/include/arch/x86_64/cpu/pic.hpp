#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_PIC_HPP_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_PIC_HPP_

#include <stdint.h>

namespace arch {
/// \brief Map two interrupt sources using the Programmable Interrupt Controller (PIC).
///
/// This function maps two interrupt sources using the Programmable Interrupt Controller (PIC).
///
/// \param pic1 The first interrupt source.
/// \param pic2 The second interrupt source.
void pic_map(uint8_t pic1, uint8_t pic2);

/// \brief Disable the Programmable Interrupt Controller (PIC) or interrupt handling.
///
/// This function disables the Programmable Interrupt Controller (PIC) or interrupt handling.
void pic_disable();
}  // namespace arch

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_PIC_HPP_