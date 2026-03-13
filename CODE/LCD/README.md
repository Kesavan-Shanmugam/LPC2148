# LPC2148 LCD Interfacing Projects

This directory contains projects demonstrating how to interface a standard 16x2 alphanumeric Liquid Crystal Display (LCD), typically based on the HD44780 controller, with the ARM7TDMI-S based LPC2148 microcontroller.

## Hardware Overview
A standard 16x2 LCD has 16 pins, including control and data lines.
The examples in this directory use an **8-bit data mode** interface.

### Pin Connections (Based on the code)
- **Data Lines (D0-D7)**: Connected to `P0.0` through `P0.7`.
- **Register Select (RS)**: Connected to `P0.8`.
  - RS = 0: Command Mode (sending instructions like clear screen, set cursor).
  - RS = 1: Data Mode (sending characters to be displayed).
- **Enable (EN)**: Connected to `P0.9`. A high-to-low pulse on this pin latches the data or command into the LCD.
- **Read/Write (RW)**: Assumed to be hardwired to Ground (0) for Write-only operations, as it is not explicitly toggled in the code.

## Core Functions
The interaction with the LCD relies on precise timing and formatting of signals, implemented via two main functions:

### 1. `command(char c)`
Sends an instruction to the LCD (e.g., clear display, move cursor).
- Clears the data pins (`IOCLR0 = 0x0FF`).
- Places the command byte `c` onto the data pins (`IOSET0 = c`).
- Selects Command mode by pulling RS low (`IOCLR0 = 1<<8`).
- Generates a High-to-Low pulse on the EN pin (`IOSET0 = 1<<9`, delay, `IOCLR0 = 1<<9`, delay) to latch the command.

### 2. `data(char d)`
Sends a character to be displayed on the LCD.
- Clears the data pins (`IOCLR0 = 0x0FF`).
- Places the character byte `d` onto the data pins (`IOSET0 = d`).
- Selects Data mode by pulling RS high (`IOSET0 = 1<<8`).
- Generates a High-to-Low pulse on the EN pin to latch the data.

## Projects Included

### 1. `latter_print` (Letter Print)
Demonstrates printing a single character ('k') on the LCD.
- Configures pins `P0.0` to `P0.11` as outputs (`IODIR0 = 0x0FFF`).
- Continuously sends the `0x0E` command (Display ON, Cursor ON) and `0x80` command (Force cursor to beginning of 1st line).
- Sends the character `'k'` using the `data()` function.

### 2. `full_name_print`
Demonstrates printing a string ("kesavan") on the LCD.
- Stores the string in a character array `char k[] = {"kesavan"}`.
- Uses a `for` loop to iterate through the array.
- In each iteration, it sends the display/cursor commands, increments the cursor address (`0x80 + i`), and prints the `i`-th character of the array. This effectively prints the full name character by character across the display.
