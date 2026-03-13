# LPC2148 Bare-Metal C Projects Repository

This repository contains a collection of fundamental embedded C programming examples and driver implementations for the **NXP LPC2148** microcontroller, which is based on the 16/32-bit ARM7TDMI-S CPU.

These projects were created using **Keil uVision** and demonstrate how to initialize and interface various hardware peripherals and communication protocols by directly manipulating the memory-mapped configuration registers (bare-metal programming).

## Repository Structure (`CODE/`)

The repository is organized by peripheral or hardware component. Each subdirectory focuses on a specific interfacing topic and contains its own detailed `README.md` explaining the register logic and wiring context.

*   **[`7 SEGMENT/`](7%20SEGMENT/)**: Examples of driving single and multiplexed multi-digit common anode 7-segment displays.
*   **[`ADC/`](ADC/)**: A project demonstrating how to initialize the 10-bit Analog-to-Digital Converter and read an analog sensor value.
*   **[`DAC/`](DAC/)**: Code illustrating how to use the 10-bit Digital-to-Analog Converter to generate output voltages.
*   **[`I2C/`](I2C/)**: Master transmitter and receiver implementations for the $I^2C$ protocol, typically used for EEPROM interfacing.
*   **[`LCD/`](LCD/)**: Driver code for a standard 16x2 alphanumeric HD44780-compatible LCD in 8-bit mode.
*   **[`LED/`](LED/)**: Basic GPIO output examples demonstrating various LED flashing and shifting patterns.
*   **[`PLL/`](PLL/)**: Foundational code for configuring the Phase Locked Loop to boost the system clock (`CCLK`) up to the maximum 60 MHz.
*   **[`SPI/`](SPI/)**: Master full-duplex communication implementations using the SPI bus to interface with synchronous serial devices.
*   **[`SWITCH/`](SWITCH/)**: GPIO input handling, mapping tactical push buttons with logical conditions to trigger outputs.
*   **[`TIMER/`](TIMER/)**: Creating precise hardware-based delays using the 32-bit Timer/Counter modules.
*   **[`UART0/`](UART0/)**: Polling-based serial transmission and reception via the Universal Asynchronous Receiver-Transmitter.

## Development Environment
*   **MCU**: NXP LPC2148 (ARM7TDMI-S)
*   **IDE**: Keil uVision (generates `.axf`, `.hex`, `.uvopt`, etc. files found alongside the source code)
*   **Language**: C (Bare-Metal)
*   **Header**: `<lpc214x.h>`

## General Code Conventions used in this Repo
- **Clocks**: The majority of the projects initialize the PLL upon startup to run at **60 MHz** System Clock (CCLK) and 60 MHz Peripheral Clock (PCLK).
- **Delays**: Many simple examples use blocking `for`-loop based software delays (`void delay()`). High-performance examples should ideally utilize the Timer modules as demonstrated in the [`TIMER/`](TIMER/) directory.
- **Port Naming**: Registers like `IODIR0`, `IOSET0`, and `IOCLR0` belong to GPIO `PORT0`. `PORT1` registers are identified by `1` (e.g., `IODIR1`).

*Note: The code logic is designed for educational breakdown of registers and flag polling mechanisms.*
