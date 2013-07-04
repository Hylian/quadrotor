#include "status_codes.h"

#ifndef _CC1101_H
#define _CC1101_H 1

#define CC1101_PA_TABLESIZE 8

// CC1101 STROBE, CONTROL AND STATUS REGISTER
#define CC1101_IOCFG2       0x29        // GDO2 output pin configuration
#define CC1101_IOCFG1       0x2E        // GDO1 output pin configuration
#define CC1101_IOCFG0D      0x06        // GDO0 output pin configuration
#define CC1101_FIFOTHR      0x07        // RX FIFO and TX FIFO thresholds
#define CC1101_SYNC1        0xD3        // Sync word, high byte
#define CC1101_SYNC0        0x91        // Sync word, low byte
#define CC1101_PKTLEN       0xFF        // Packet length
#define CC1101_PKTCTRL1     0x04        // Packet automation control
#define CC1101_PKTCTRL0     0x05        // Packet automation control
#define CC1101_ADDR         0x00        // Device address
#define CC1101_CHANNR       0x14        // Channel number
#define CC1101_FSCTRL1      0x0C        // Frequency synthesizer control
#define CC1101_FSCTRL0      0x00        // Frequency synthesizer control
#define CC1101_FREQ2        0x22        // Frequency control word, high byte
#define CC1101_FREQ1        0xB1        // Frequency control word, middle byte
#define CC1101_FREQ0        0x3B        // Frequency control word, low byte
#define CC1101_MDMCFG4      0x2D        // Modem configuration
#define CC1101_MDMCFG3      0x3B        // Modem configuration
#define CC1101_MDMCFG2      0x13        // Modem configuration
#define CC1101_MDMCFG1      0x22        // Modem configuration
#define CC1101_MDMCFG0      0xF8        // Modem configuration
#define CC1101_DEVIATN      0x62        // Modem deviation setting
#define CC1101_MCSM2        0x07        // Main Radio Control State Machine configuration
#define CC1101_MCSM1        0x30        // Main Radio Control State Machine configuration
#define CC1101_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CC1101_FOCCFG       0x1D        // Frequency Offset Compensation configuration
#define CC1101_BSCFG        0x1C        // Bit Synchronization configuration
#define CC1101_AGCCTRL2     0xC7        // AGC control
#define CC1101_AGCCTRL1     0x00        // AGC control
#define CC1101_AGCCTRL0     0xB0        // AGC control
#define CC1101_WOREVT1      0x87        // High byte Event 0 timeout
#define CC1101_WOREVT0      0x6B        // Low byte Event 0 timeout
#define CC1101_WORCTRL      0xFB        // Wake On Radio control
#define CC1101_FREND1       0xB6        // Front end RX configuration
#define CC1101_FREND0       0x10        // Front end TX configuration
#define CC1101_FSCAL3       0xEA        // Frequency synthesizer calibration
#define CC1101_FSCAL2       0x2A        // Frequency synthesizer calibration
#define CC1101_FSCAL1       0x00        // Frequency synthesizer calibration
#define CC1101_FSCAL0       0x1F        // Frequency synthesizer calibration
#define CC1101_RCCTRL1      0x41        // RC oscillator configuration
#define CC1101_RCCTRL0      0x00        // RC oscillator configuration
#define CC1101_FSTEST       0x59        // Frequency synthesizer calibration control
#define CC1101_PTEST        0x7F        // Production test
#define CC1101_AGCTEST      0x3F        // AGC test
#define CC1101_TEST2        0x88       // Various test settings
#define CC1101_TEST1        0x31        // Various test settings
#define CC1101_TEST0        0x09        // Various test settings

// Strobe commands
#define CC1101_SRES         0x30        // Reset chip.
#define CC1101_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
// If in RX/TX: Go to a wait state where only the synthesizer is
// running (for quick RX / TX turnaround).
#define CC1101_SXOFF        0x32        // Turn off crystal oscillator.
#define CC1101_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
// (enables quick start).
#define CC1101_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
// MCSM0.FS_AUTOCAL=1.
#define CC1101_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
// MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
// Only go to TX if channel is clear.
#define CC1101_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
// Wake-On-Radio mode if applicable.
#define CC1101_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CC1101_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CC1101_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CC1101_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CC1101_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CC1101_SWORRST      0x3C        // Reset real time clock.
#define CC1101_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
// bytes for simpler software.
// Status registers (read & burst)
#define CC1101_PARTNUM      (0x30 | 0xc0)
#define CC1101_VERSION      (0x31 | 0xc0)
#define CC1101_FREQEST      (0x32 | 0xc0)
#define CC1101_LQI          (0x33 | 0xc0)
#define CC1101_RSSI         (0x34 | 0xc0)
#define CC1101_MARCSTATE    (0x35 | 0xc0)
#define CC1101_WORTIME1     (0x36 | 0xc0)
#define CC1101_WORTIME0     (0x37 | 0xc0)
#define CC1101_PKTSTATUS    (0x38 | 0xc0)
#define CC1101_VCO_VC_DAC   (0x39 | 0xc0)
#define CC1101_TXBYTES      (0x3A | 0xc0)
#define CC1101_RXBYTES      (0x3B | 0xc0)

#define CC1101_PATABLE      0x3E
#define CC1101_TXFIFO       0x3F
#define CC1101_RXFIFO       0x3F

#define CC1101_FIFO_SIZE    0x40 // 64 bytes

#define CC1101_PACKT_LEN   (CC1101_FIFO_SIZE - 3) // see section 15.3 of the datasheet

void PowerOnStartUp(); // manual power on reset as described in  27.1 of cc1100 datasheet
char CCRead(char addr, char* data);
char CCReadBurst(char addr, char* dataPtr, char size);
char CCWrite(char addr, char data);
char CCWriteBurst(char addr, const char* dataPtr, char size);
char CCStrobe(char addr);
void CCSetup(); // configure registers
void CCsetPA(char paIndex); // set power amplification using a table
char CCRSSIdecode(char rssiEnc); // decode RSSI value

#endif