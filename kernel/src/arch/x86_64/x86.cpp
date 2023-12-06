#include <x86.h>
#include <dev/serials.hpp>

/**
 * @brief Architecture specific initialization for the kernel.
 *  1) Initializes Serial port on COM1 and checks whether the serial port is faulty.
 *  
 */
void arch_initialize() {
    if (!dev::gserial.initialize(SERIAL_COM1)) {
        dev::gserial.write("Serial chip is faulty!\n");
    }
}