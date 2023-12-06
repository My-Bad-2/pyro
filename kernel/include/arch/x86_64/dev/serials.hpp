#ifndef KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H_
#define KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H_

#include <stddef.h>
#include <stdint.h>

#define SERIAL_COM1 0x3F8
#define SERIAL_COM2 0x2F8
#define SERIAL_COM3 0x3E8
#define SERIAL_COM4 0x2E8

namespace serials {
enum registers {
    Data = 0,
    Interrupt = 1,
    BaudRateLow = 0,
    BaudRateHigh = 1,
    InterruptIdentifactor = 2,
    FifoController = 2,
    LineControl = 3,
    ModemControl = 4,
    LineStatus = 5,
    ModemStatus = 6,
    ScratchRegister = 7
};

enum line_controls {
    DataSize5 = 0,
    DataSize6 = 1,
    DataSize7 = 2,
    DataSize8 = 3,
    DlabStatus = (1 << 7)
};

enum modem_control {
    ModemDtr = (1 << 0),
    ModemRts = (1 << 1),
    ModemOut1 = (1 << 2),
    ModemOut2 = (1 << 3),
    ModemLoopback = (1 << 4)
};

enum interrupt {
    WhenDataAvailable = (1 << 0),
    WhenTransmitterEmpty = (1 << 1),
    WhenBreakEmpty = (1 << 2),
    WhenStatusUpdate = (1 << 3),
};

enum line_status {
    DataReady = (1 << 0),
    OverrunError = (1 << 1),
    ParityError = (1 << 2),
    FramingError = (1 << 3),
    BreakIndicator = (1 << 4),
    TransmitterBufEmpty = (1 << 5),
    TransmitterEmpty = (1 << 6),
    ImpendingError = (1 << 7)
};

enum baud {
    Baud50 = 2304,
    Baud110 = 1047,
    Baud220 = 524,
    Baud300 = 384,
    Baud600 = 192,
    Baud1200 = 96,
    Baud2400 = 48,
    Baud4800 = 24,
    Baud9600 = 12,
    Baud19200 = 6,
    Baud38400 = 3,
    Baud57600 = 2,
    Baud115200 = 1
};

enum fifo_Control {
    EnableFIFO = (1 << 0),
    ClearReceiveFIFO = (1 << 1),
    ClearTransmitFIFO = (1 << 2),
    Enable64ByteFIFO = (1 << 5),
    TriggerLevel1 = (0 << 6),
    TriggerLevel2 = (1 << 6),
    TriggerLevel3 = (2 << 6),
    TriggerLevel4 = (3 << 6)
};
}  // namespace serials

namespace dev {
class serial_device {
   public:
    serial_device() = default;

    ~serial_device() {}

    bool initialize(uint16_t port);

    void putc(uint8_t ch);
    uint8_t getc();

    void write(const char* str);

   private:
    void write_reg(serials::registers reg, uint8_t val);
    uint8_t read_reg(serials::registers reg);

   private:
    uint16_t serial_port;
};

extern serial_device gserial;
}  // namespace dev

#endif
