#include <x86.h>
#include <dev/serials.hpp>
#include <system/log.hpp>

logger arch_logger("arch.initialize");

/**
 * @brief Architecture specific initialization for the kernel.
 *  1) Initializes Serial port on COM1 and checks whether the serial port is faulty.
 *  
 */
void arch_initialize() {
    if (!dev::gserial.initialize(SERIAL_COM1)) {
        arch_logger.log(LOG_LEVEL_WARNING, "Serial chip is faulty!\n");
    }
}