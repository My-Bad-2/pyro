#include <string.h>
#include <sys/types.h>
#include <x86.h>
#include <dev/serials.hpp>

namespace dev {
serial_device gserial;

/**
 * @brief Writes an `unsigned char` value to selected serial port offsetted by `reg`.
 * 
 * @param reg offset
 * @param val value to write
 */
void serial_device::write_reg(serials::registers reg, uint8_t val) {
    outp(serial_port + reg, val);
}

/**
 * @brief Reads an `unsigned char` value from the selected serial port offsetted by `reg`
 * 
 * @param reg offset
 * @return uint8_t 
 */
uint8_t serial_device::read_reg(serials::registers reg) {
    return inp(serial_port + reg);
}

/**
 * @brief Send an unsigned char to the selected serial port
 * 
 * @param ch character
 */
void serial_device::putc(uint8_t ch) {
    while (!(read_reg(serials::LineStatus) & serials::TransmitterBufEmpty)) {
        asm volatile("pause");
    }

    write_reg(serials::Data, ch);
}

/**
 * @brief Gets an unsigned char from the selected serial port
 * 
 * @return uint8_t character
 */
uint8_t serial_device::getc() {
    while (!(read_reg(serials::LineStatus) & serials::DataReady)) {
        asm volatile("pause");
    }

    return read_reg(serials::Data);
}

/**
 * @brief Sends a streams of bytes to the selected serial port
 * 
 * @param string stream of bytes
 */
void serial_device::write(const char* string) {
    size_t length = strlen(string);

    for (size_t i = 0; i < length; i++) {
        putc(string[i]);
    }
}

/**
 * @brief Initialize the driver for a serial port `port` and verify if the `port`
 *  is faulty or not.
 * 
 * @param port serial port
 * @return true The serial port isn't faulty
 * @return false The serial port is faulty
 */
bool serial_device::initialize(uint16_t port) {
    serial_port = port;

    // Disable all interrupts
    write_reg(serials::InterruptIdentifactor, 0x00);

    // Enable DLAB (set baud rate divisor)
    write_reg(serials::LineControl, serials::DlabStatus);

    // Set divisor to 3 (lo byte) 38400 baud
    write_reg(serials::BaudRateLow, serials::Baud38400);

    // Set divisor to 3 (hi byte) baud
    write_reg(serials::BaudRateHigh, 0x00);

    // 8 bits, no parity, one stop bit
    write_reg(serials::LineControl, serials::DataSize8);

    // Enable FIFO, Clear themm with 14-byte threshold
    write_reg(serials::FifoController,
              serials::EnableFIFO | serials::ClearReceiveFIFO |
                  serials::ClearTransmitFIFO | serials::TriggerLevel4);

    // IRQs enabled, RTS/DSR set
    write_reg(serials::ModemControl,
              serials::ModemRts | serials::ModemDtr | serials::ModemOut2);

    // set in loopback mode, test the serial chip
    write_reg(serials::ModemControl,
              serials::ModemLoopback | serials::ModemRts | serials::ModemOut1 |
                  serials::ModemOut2);

    // Test the serial chip (send byte 0xAE and check if serial returns the same byte)
    write_reg(serials::Data, 0xAE);

    if (read_reg(serials::Data) != 0xAE) {
        return false;
    }

    // If serial is not fault set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    write_reg(serials::ModemControl, serials::ModemDtr | serials::ModemRts |
                                         serials::ModemOut1 |
                                         serials::ModemOut2);

    return true;
}
}  // namespace dev