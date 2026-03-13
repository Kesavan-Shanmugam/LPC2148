# LPC2148 I2C (Inter-Integrated Circuit) Communication

This directory contains projects demonstrating serial communication using the Inter-Integrated Circuit (I2C) protocol on the ARM7TDMI-S based LPC2148 microcontroller.

## Hardware Overview
The LPC2148 has two I2C bus interfaces: I2C0 and I2C1. The examples here use **I2C0**.
- **SCL0 (Serial Clock)**: Mapped to pin `P0.2`.
- **SDA0 (Serial Data)**: Mapped to pin `P0.3`.
I2C is a synchronous, half-duplex communication protocol widely used for connecting lower-speed peripherals, like EEPROMs, RTCs, and sensors.

## Key Registers Used
1. **`PINSEL0`**: Configures pins `P0.2` and `P0.3` to their alternate functions (SCL0 and SDA0).
2. **`I2C0CONSET` (I2C Control Set Register)**: Used to set control bits (Enable I2C, START flag, STOP flag, Acknowledge flag).
3. **`I2C0CONCLR` (I2C Control Clear Register)**: Used to clear control bits, most importantly the **Interrupt flag (`SI`)** after an I2C state changes to allow the hardware to proceed to the next state.
4. **`I2C0SCLH` & `I2C0SCLL`**: Define the high and low duty cycles of the SCL clock, effectively setting the I2C bus speed.
5. **`I2C0STAT` (I2C Status Register)**: Contains the status code of the last bus operation.
6. **`I2C0DAT` (I2C Data Register)**: Holds the byte to be transmitted or the byte just received.

## Project Analysis

### Initialization (`i2c_init()`)
```c
PINSEL0 = 0x50;        // Select SCL0 on P0.2 and SDA0 on P0.3
I2C0CONCLR = 0x6C;     // Clear AAC, SIC, STAC, I2ENC (Reset state)
I2C0SCLH = 0x96;       // Set SCL High duty cycle (150)
I2C0SCLL = 0x96;       // Set SCL Low duty cycle (150)
I2C0CONSET = 0x40;     // Enable I2C0 (I2EN = 1)
```

### 1. `transmit` (Master Transmitter)
This project acts as a Master writing data to a Slave device (like an EEPROM).
- **Start Condition**: Sets the START bit (`0x20`) and waits for the status `0x08` (A START condition has been transmitted).
- **Write Sequence (`i2c_write(char w)`)**:
  - Sends Slave Address + Write Bit (`0xA0`) and waits for interrupt flag.
  - Sends High Memory Address byte (`0x00`) and waits.
  - Sends Low Memory Address byte (`0x00`) and waits.
  - Sends the actual Data byte (`w`) and waits.
- **Stop Condition**: Sets the STOP bit (`0x10`).

### 2. `receive` (Master Receiver)
This project reads data from a Slave device and displays it on an LCD connected to `PORT1`.
- **Read Sequence (`i2c_read()`)**:
  - Note: The provided `i2c_read()` function logic seems incomplete for a typical EEPROM read. It directly sends a Slave Address + Read Bit (`0xA1`), then sends a dummy byte `0x0C` (which is unusual when reading unless it's a specific slave protocol), and then reads `I2C0DAT`. A standard random read usually involves a dummy write to set the memory address, followed by a Repeated Start, and then the read command.
  - The LCD part is shifted to `PORT1` (`P1.16` to `P1.25`) because `PORT0` pins 2 and 3 are occupied by I2C.

### Note on Interrupt Polling
In bare-metal I2C programming on the LPC21xx, almost every action (sending start, sending address, sending data) causes an internal state machine change, which flags an interrupt (bit 3 in `I2C0CONSET`). The code uses polling (`while((I2C0CONSET & 0x08) == 0);`) to wait for each step to finish, then clears the flag (`I2C0CONCLR = 0x08;`) to proceed to the next step.
