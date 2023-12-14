#include <sys/types.h>
#include <system/log.h>
#include <x86.h>
#include <dev/serials.hpp>

namespace dev {
/// Global instance of the serial_device class for serial communication.
serial_device gserial;

/// \brief Write a value to a specified register of the serial port.
///
/// This member function of the `serial_device` class is responsible for writing a value to a specified
/// register of the serial port. It takes two parameters:
///   - `reg`: A value from the `serials::registers` enumeration indicating the register to write to.
///   - `val`: The 8-bit value to be written to the specified register.
///
/// The function uses the `outp()` function to perform the actual write operation to the serial port.
///
/// \note The behavior of this function depends on the specifics of the hardware and the implementation
///       of the `outp()` function.
///
/// \param reg The register to write to.
/// \param val The 8-bit value to be written to the specified register.
void serial_device::write_reg(serials::registers reg, uint8_t val) {
    outp(serial_port + reg, val);
}

/// \brief Read the value from a specified register of the serial port.
///
/// This member function of the `serial_device` class is responsible for reading the value from a specified
/// register of the serial port. It takes one parameter:
///   - `reg`: A value from the `serials::registers` enumeration indicating the register to read from.
///
/// The function uses the `inp()` function to perform the actual read operation from the serial port.
/// It returns the 8-bit value read from the specified register.
///
/// \note The behavior of this function depends on the specifics of the hardware and the implementation
///       of the `inp()` function.
///
/// \param reg The register to read from.
/// \return The 8-bit value read from the specified register.
uint8_t serial_device::read_reg(serials::registers reg) {
    return inp(serial_port + reg);
}

/// \brief Transmit a single character over the serial port.
///
/// This member function of the `serial_device` class is responsible for transmitting a single character
/// over the serial port. It takes one parameter:
///   - `ch`: The 8-bit character to be transmitted.
///
/// The function uses busy-waiting to ensure that the serial transmitter buffer is empty before writing
/// the character to the serial port's data register.
///
/// \note The behavior of this function depends on the specifics of the hardware and the implementation
///       of `read_reg()`, `write_reg()`, and any underlying assembly instructions.
///
/// \param ch The character to be transmitted.
void serial_device::putc(uint8_t ch) {
    // Wait until the Transmitter Buffer Empty bit in the Line Status register is set
    while (!(read_reg(serials::LineStatus) & serials::TransmitterBufEmpty)) {
        // Use the "pause" instruction to provide a hint to the processor that it is in a spin-wait loop
        asm volatile("pause");
    }

    // Write the character 'ch' to the serial port's data register
    write_reg(serials::Data, ch);
}

/// \brief Receive a single character from the serial port.
///
/// This member function of the `serial_device` class is responsible for receiving a single character
/// from the serial port. It uses busy-waiting to ensure that data is ready in the receiver buffer
/// before reading the character from the serial port's data register.
///
/// \note The behavior of this function depends on the specifics of the hardware and the implementation
///       of `read_reg()` and any underlying assembly instructions.
///
/// \return The received 8-bit character.
uint8_t serial_device::getc() {
    // Wait until the Data Ready bit in the Line Status register is set
    while (!(read_reg(serials::LineStatus) & serials::DataReady)) {
        // Use the "pause" instruction to provide a hint to the processor that it is in a spin-wait loop
        asm volatile("pause");
    }

    // Return the 8-bit character read from the serial port's data register
    return read_reg(serials::Data);
}

/// \brief Write a null-terminated string to the serial port.
///
/// This member function of the `serial_device` class is responsible for writing a null-terminated
/// string to the serial port. It iterates through each character of the string and transmits it
/// using the `putc()` function.
///
/// \param string Pointer to the null-terminated string to be written.
void serial_device::write(const char* string) {
    // Iterate through each character and transmit it using the `putc()` function
    for (size_t i = 0; string[i] != '\0'; i++) {
        putc(string[i]);
    }
}

/// \brief Initialize the serial port with the specified parameters.
///
/// This member function of the `serial_device` class is responsible for initializing the serial port
/// with the specified parameters, including baud rate, data size, parity, stop bits, and FIFO settings.
/// It performs the following initialization steps:
///   - Sets the serial port's base address.
///   - Disables interrupts.
///   - Sets the baud rate divisor for the desired baud rate.
///   - Configures data size, parity, and stop bits.
///   - Enables FIFO and sets FIFO trigger levels.
///   - Enables modem control signals.
///   - Puts the serial chip in loopback mode and tests its functionality.
///   - If the test is successful, sets the serial chip in normal operation mode.
///
/// \param port The base address of the serial port.
/// \return True if the serial port is successfully initialized, false otherwise.
bool serial_device::initialize(uint16_t port) {
    // Set the serial port's base address
    serial_port = port;

    // Disable all interrupts
    write_reg(serials::InterruptIdentifactor, 0x00);

    // Enable DLAB (set baud rate divisor)
    write_reg(serials::LineControl, serials::DlabStatus);

    // Set divisor to 3 (lo byte) for 38400 baud
    write_reg(serials::BaudRateLow, serials::Baud38400);

    // Set divisor to 3 (hi byte) for 38400 baud
    write_reg(serials::BaudRateHigh, 0x00);

    // Configure for 8 bits, no parity, one stop bit
    write_reg(serials::LineControl, serials::DataSize8);

    // Enable FIFO, clear them with 14-byte threshold
    write_reg(serials::FifoController,
              serials::EnableFIFO | serials::ClearReceiveFIFO |
                  serials::ClearTransmitFIFO | serials::TriggerLevel4);

    // Enable IRQs, set RTS/DSR
    write_reg(serials::ModemControl,
              serials::ModemRts | serials::ModemDtr | serials::ModemOut2);

    // Set in loopback mode, test the serial chip
    write_reg(serials::ModemControl,
              serials::ModemLoopback | serials::ModemRts | serials::ModemOut1 |
                  serials::ModemOut2);

    // Test the serial chip by sending byte 0xAE and checking if it returns the same byte
    write_reg(serials::Data, 0xAE);

    if (read_reg(serials::Data) != 0xAE) {
        return false;
    }

    // If the serial chip test is successful, set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    write_reg(serials::ModemControl, serials::ModemDtr | serials::ModemRts |
                                         serials::ModemOut1 |
                                         serials::ModemOut2);

    log_message(LOG_LEVEL_INFO, "Successfully Initialized Serials");
    return true;
}
}  // namespace dev

/// \brief External C function to transmit a character using the global serial device.
///
/// This function serves as an interface to transmit a character using the global serial device
/// (`dev::gserial`). It is declared with the `extern "C"` linkage to ensure compatibility with
/// C code.
///
/// \param c The character to be transmitted.
extern "C" void putc(char c) {
    // Transmit the character using the global serial device
    dev::gserial.putc(c);
}