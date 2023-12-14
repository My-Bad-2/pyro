#ifndef KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H_
#define KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H_

#include <stddef.h>
#include <stdint.h>

/// \def SERIAL_COM1
/// \brief Base address for COM1 serial port.
#define SERIAL_COM1 0x3F8

/// \def SERIAL_COM2
/// \brief Base address for COM2 serial port.
#define SERIAL_COM2 0x2F8

/// \def SERIAL_COM3
/// \brief Base address for COM3 serial port.
#define SERIAL_COM3 0x3E8

/// \def SERIAL_COM4
/// \brief Base address for COM4 serial port.
#define SERIAL_COM4 0x2E8

namespace serials {
/// \enum registers
/// \brief Enumeration representing UART registers.
enum registers {
    Data = 0,                   ///< Data Register
    Interrupt = 1,              ///< Interrupt Enable Register
    BaudRateLow = 0,            ///< Baud Rate (Low Byte) Register
    BaudRateHigh = 1,           ///< Baud Rate (High Byte) Register
    InterruptIdentifactor = 2,  ///< Interrupt Identifactor Register
    FifoController = 2,         ///< FIFO Controller Register
    LineControl = 3,            ///< Line Control Register
    ModemControl = 4,           ///< Modem Control Register
    LineStatus = 5,             ///< Line Status Register
    ModemStatus = 6,            ///< Modem Status Register
    ScratchRegister = 7         ///< Scratch Register
};

/// \enum line_controls
/// \brief Enumeration representing line control options for UART.
enum line_controls {
    DataSize5 = 0,         ///< Data Size: 5 bits
    DataSize6 = 1,         ///< Data Size: 6 bits
    DataSize7 = 2,         ///< Data Size: 7 bits
    DataSize8 = 3,         ///< Data Size: 8 bits
    DlabStatus = (1 << 7)  ///< Divisor Latch Access Bit (DLAB)
};

/// \enum modem_control
/// \brief Enumeration representing modem control options for UART.
enum modem_control {
    ModemDtr = (1 << 0),      ///< Data Terminal Ready (DTR)
    ModemRts = (1 << 1),      ///< Request to Send (RTS)
    ModemOut1 = (1 << 2),     ///< Output 1
    ModemOut2 = (1 << 3),     ///< Output 2
    ModemLoopback = (1 << 4)  ///< Loopback Mode
};

/// \enum interrupt
/// \brief Enumeration representing interrupt conditions for UART.
enum interrupt {
    WhenDataAvailable = (1 << 0),     ///< Interrupt when data is available
    WhenTransmitterEmpty = (1 << 1),  ///< Interrupt when transmitter is empty
    WhenBreakEmpty = (1 << 2),        ///< Interrupt when break is empty
    WhenStatusUpdate = (1 << 3)       ///< Interrupt when status is updated
};

/// \enum line_status
/// \brief Enumeration representing line status conditions for UART.
enum line_status {
    DataReady = (1 << 0),            ///< Data Ready
    OverrunError = (1 << 1),         ///< Overrun Error
    ParityError = (1 << 2),          ///< Parity Error
    FramingError = (1 << 3),         ///< Framing Error
    BreakIndicator = (1 << 4),       ///< Break Indicator
    TransmitterBufEmpty = (1 << 5),  ///< Transmitter Buffer Empty
    TransmitterEmpty = (1 << 6),     ///< Transmitter Empty
    ImpendingError = (1 << 7)        ///< Impending Error
};

/// \enum baud
/// \brief Enumeration representing common baud rates for UART.
enum baud {
    Baud50 = 2304,   ///< Baud Rate: 50
    Baud110 = 1047,  ///< Baud Rate: 110
    Baud220 = 524,   ///< Baud Rate: 220
    Baud300 = 384,   ///< Baud Rate: 300
    Baud600 = 192,   ///< Baud Rate: 600
    Baud1200 = 96,   ///< Baud Rate: 1200
    Baud2400 = 48,   ///< Baud Rate: 2400
    Baud4800 = 24,   ///< Baud Rate: 4800
    Baud9600 = 12,   ///< Baud Rate: 9600
    Baud19200 = 6,   ///< Baud Rate: 19200
    Baud38400 = 3,   ///< Baud Rate: 38400
    Baud57600 = 2,   ///< Baud Rate: 57600
    Baud115200 = 1   ///< Baud Rate: 115200
};

/// \enum fifo_Control
/// \brief Enumeration representing FIFO control options for UART.
enum fifo_Control {
    EnableFIFO = (1 << 0),         ///< Enable FIFO
    ClearReceiveFIFO = (1 << 1),   ///< Clear Receive FIFO
    ClearTransmitFIFO = (1 << 2),  ///< Clear Transmit FIFO
    Enable64ByteFIFO = (1 << 5),   ///< Enable 64-byte FIFO
    TriggerLevel1 = (0 << 6),      ///< Trigger Level: 1 byte
    TriggerLevel2 = (1 << 6),      ///< Trigger Level: 2 bytes
    TriggerLevel3 = (2 << 6),      ///< Trigger Level: 3 bytes
    TriggerLevel4 = (3 << 6)       ///< Trigger Level: 4 bytes
};
}  // namespace serials

namespace dev {
/// \brief Class representing a serial communication device.
class serial_device {
   public:
    /// \brief Default constructor.
    serial_device() = default;

    /// \brief Destructor.
    ~serial_device() {}

    /// \brief Initialize the serial device with the specified port.
    ///
    /// \param port The base address of the serial port.
    /// \return True if initialization is successful, false otherwise.
    bool initialize(uint16_t port);

    /// \brief Transmit a single character over the serial port.
    ///
    /// \param ch The character to be transmitted.
    void putc(uint8_t ch);

    /// \brief Receive a single character from the serial port.
    ///
    /// \return The received 8-bit character.
    uint8_t getc();

    /// \brief Write a null-terminated string to the serial port.
    ///
    /// \param str Pointer to the null-terminated string to be written.
    void write(const char* str);

   private:
    /// \brief Write a value to a specified register of the serial port.
    ///
    /// \param reg The register to write to.
    /// \param val The 8-bit value to be written to the specified register.
    void write_reg(serials::registers reg, uint8_t val);

    /// \brief Read the value from a specified register of the serial port.
    ///
    /// \param reg The register to read from.
    /// \return The 8-bit value read from the specified register.
    uint8_t read_reg(serials::registers reg);

   private:
    uint16_t serial_port;  ///< Base address of the serial port.
};

/// External declaration for the global instance of the `serial_device` class.
extern serial_device gserial;
}  // namespace dev

#endif  // KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H_