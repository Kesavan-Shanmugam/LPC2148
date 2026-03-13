# LPC2148 SPI (Serial Peripheral Interface) Communication

This directory contains projects demonstrating full-duplex synchronous serial communication using the SPI0 interface on the ARM7TDMI-S based LPC2148 microcontroller. The projects specifically target reading and writing to an external SPI device (likely an EEPROM like the 25AA640).

## Hardware Overview
The LPC2148 features two SPI controllers (SPI0 and SPI1/SSP). These examples use **SPI0**.
- **SCK0 (Serial Clock)**: Mapped to `P0.4`.
- **MISO0 (Master In Slave Out)**: Mapped to `P0.5`.
- **MOSI0 (Master Out Slave In)**: Mapped to `P0.6`.
- **CS / SSEL0 (Slave Select)**: Mapped to `P0.7`. In Master mode, it's often driven manually as a standard GPIO.

## Key Registers Used
1. **`PINSEL0`**: Configures pins `P0.4` to `P0.6` as SCK0, MISO0, and MOSI0.
2. **`S0SPCR` (SPI Control Register)**: Sets operational mode (Master/Slave), clock phase/polarity (CPHA/CPOL), bit enable, and data order (LSB/MSB first).
3. **`S0SPCCR` (SPI Clock Counter Register)**: Divides the PCLK to generate the SPI clock rate. Must be an even number $\ge$ 8.
4. **`S0SPSR` (SPI Status Register)**: Contains the SPI interrupt flag (SPIF, bit 7) which goes high when a data transfer is complete.
5. **`S0SPDR` (SPI Data Register)**: Writing to this register initiates a transmission. Reading from it retrieves received data.

## Project Analysis

### Initialization (`SPI_INIT()`)
```c
IODIR0 = (1<<7);          // Set P0.7 (CS) as output
PINSEL0 = 0x00001500;     // Select SCK0, MISO0, MOSI0 on P0.4 to P0.6
S0SPCR = 0x0020;          // Enable Master Mode (MSTR=1)
S0SPCCR = 0x3C;           // SPI Clock divisor (60 decimal = 0x3C)
```

### 1. `transmit` (Writing to EEPROM)
This project acts as an SPI Master writing a byte to an EEPROM.
- The `SPI_write()` function manually controls the Chip Select (CS) pin (`P0.7`) to frame the transaction.
- **EEPROM Write Sequence**:
  - Pull CS LOW.
  - Send Write Enable instruction (`0x06`) and wait for `SPIF` flag in `S0SPSR`.
  - Pull CS HIGH, delay, then pull CS LOW to start a new command frame.
  - Send Write command (`0x02`), wait.
  - Send Memory Address Low Byte (`0x00`), wait.
  - Send Memory Address High Byte (`0x00`), wait. Note: The code sends Low then High, which is reverse mapping compared to standard EEPROMs which usually expect High Byte then Low Byte.
  - Send Data byte (`w`), wait.
  - Pull CS HIGH to complete the write cycle.

### 2. `receive` (Reading from EEPROM)
This project acts as an SPI Master reading a byte from an EEPROM and displaying it on an LCD.
- **EEPROM Read Sequence**:
  - Pull CS LOW.
  - Send Read command (`0x03`), wait.
  - Send Memory Address High Byte (`0x00`), wait.
  - Send Memory Address Low Byte (`0x00`), wait. (Notice the order is inverted compared to the transmit code).
  - Send dummy byte (`0xFF`) to generate the clock pulses needed to receive the data from the Slave. Wait for `SPIF`.
  - Read the received byte: `data = S0SPDR`.
  - Pull CS HIGH.
- Displays the received `data` byte on the LCD connected to `PORT1`.
