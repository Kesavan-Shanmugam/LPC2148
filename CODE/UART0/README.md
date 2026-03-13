# LPC2148 UART0 Communication

This directory contains projects demonstrating serial communication via the Universal Asynchronous Receiver/Transmitter (UART0) on the ARM7TDMI-S based LPC2148 microcontroller.

## Hardware Overview
The LPC2148 contains two standard UARTs: UART0 and UART1.
UART0 uses the following pins:
- **TXD0 (Transmit Data)**: Mapped to `P0.0`.
- **RXD0 (Receive Data)**: Mapped to `P0.1`.

## Key Registers Used
1. **`PINSEL0`**: Configures pins `P0.0` and `P0.1` as TXD0 and RXD0 respectively.
2. **`U0LCR` (Line Control Register)**: Determines the data format (word length, stop bits, parity) and enables the Divisor Latch Access Bit (DLAB) to set the baud rate.
3. **`U0DLL` & `U0DLM` (Divisor Latch Registers)**: Used to configure the required baud rate based on the Peripheral Clock (PCLK).
4. **`U0LSR` (Line Status Register)**: Contains flags to indicate if the receive buffer has data (`RDR` - bit 0) or if the transmit holding register is empty (`THRE` - bit 5).
5. **`U0THR` (Transmit Holding Register)**: Writing a byte to this register initiates transmission.
6. **`U0RBR` (Receiver Buffer Register)**: Reading from this register gets the received byte.

## Initialization (`INIT_UART`)
Both transmit and receive projects use the same initialization sequence:
```c
PINSEL0 |= 0x05;     // Select TXD0 and RXD0 on P0.0 and P0.1
U0LCR = 0x83;        // Enable DLAB (bit 7 = 1), 8-bit character length (bits 1:0 = 11)
U0DLL = 0x87;        // Set divisor low byte
U0DLM = 0x01;        // Set divisor high byte
U0LCR = 0x03;        // Disable DLAB, lock baud rate settings
```
*Note: The divisor values (0x0187) calculate a specific baud rate (typically 9600) based on the PLL configuration of PCLK.*

## Projects Included

### 1. `transmit`
Demonstrates sending a single character via UART0 in a polling manner.
- **Function `write(char k)`**:
  - Waits until the Transmitter Holding Register Empty (THRE) flag in `U0LSR` (bit 5) is set, indicating it's ready for new data: `while(!(U0LSR&(1<<5)));`
  - Writes the character to `U0THR`.
- The `main` function initializes the PLL and UART, and transmits the character `'k'`. *Note: There is a bug in the code where `write('k');` and `delay();` are placed outside a `while(1)` loop, meaning it only executes once. Further, within `write`, the return type is `int` but it doesn't return anything. The code also contains a random `delay` followed by nothing, suggesting it's incomplete or meant to be wrapped in a loop.*

### 2. `receive`
Demonstrates receiving a single character via UART0 and simultaneously displaying it on an LCD display.
- **Function `read()`**:
  - Waits until the Receiver Data Ready (RDR) flag in `U0LSR` (bit 0) is set, indicating a character has been received: `while(!(U0LSR&(1<<0)));`
  - Returns the byte read from `U0RBR`.
- The `main` function loops continuously. It reads a character from UART0 and then passes it to the `display_data` function to show it on the LCD. *Note: Similar to the transmit code, `value=read();` is outside the `while(1)` loop. It will only wait and read one single character upon startup, and then repeatedly print that same character to the LCD infinitely.*
