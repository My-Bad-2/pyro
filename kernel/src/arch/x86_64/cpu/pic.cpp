#include <x86.h>
#include <cpu/pic.hpp>

/// \def PIC1
/// \brief Base address for Programmable Interrupt Controller 1 (PIC1).
///
/// This constant represents the base address for Programmable Interrupt Controller 1 (PIC1).
#define PIC1 0x20

/// \def PIC2
/// \brief Base address for Programmable Interrupt Controller 2 (PIC2).
///
/// This constant represents the base address for Programmable Interrupt Controller 2 (PIC2).
#define PIC2 0xA0

/// \def ICW1
/// \brief Initialization Control Word 1 (ICW1) value.
///
/// ICW1 is used during the initialization of the Programmable Interrupt Controllers.
/// This constant represents the value for ICW1.
#define ICW1 0x11

/// \def ICW4
/// \brief Initialization Control Word 4 (ICW4) value.
///
/// ICW4 is used during the initialization of the Programmable Interrupt Controllers.
/// This constant represents the value for ICW4.
#define ICW4 0x01

namespace arch {
/// \brief Initialize the Programmable Interrupt Controllers (PIC) and remap IRQs.
///
/// This function initializes the PIC by sending the necessary Initialization Command Words (ICWs)
/// to both PIC1 and PIC2. It also remaps IRQs to specified interrupt vectors.
///
/// \param pic1 The interrupt vector to which PIC1 is remapped.
/// \param pic2 The interrupt vector to which PIC2 is remapped.
///
/// \note This function assumes the existence of the following constants:
/// - PIC1: Base address of PIC1.
/// - PIC2: Base address of PIC2.
/// - ICW1, ICW2, ICW3, ICW4: Specific values for the Initialization Command Words.
void pic_map(uint8_t pic1, uint8_t pic2) {
    // send ICW1
    outp(PIC1, ICW1);
    outp(PIC2, ICW1);

    // send ICW2
    outp(PIC1 + 1, pic1);  // remap
    outp(PIC2 + 1, pic2);  // pics

    // send ICW3
    outp(PIC1 + 1, 4);  // IRQ2 -> connection to slave
    outp(PIC2 + 1, 2);

    // send ICW4
    outp(PIC1 + 1, 5);
    outp(PIC2 + 1, 1);

    // disable all IRQs
    // pic_disable(); // not yet
}

/// \brief Disable all interrupts on both Programmable Interrupt Controllers (PIC).
///
/// This function disables all interrupts on both PIC1 and PIC2 by sending
/// the value 0xff to the corresponding control registers.
///
/// \note This function assumes the existence of the following constants:
/// - PIC1: Base address of PIC1.
/// - PIC2: Base address of PIC2.
void pic_disable() {
    outp(PIC2 + 1, 0xff);
    outp(PIC1 + 1, 0xff);
}
}  // namespace arch