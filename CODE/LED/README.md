# LPC2148 LED Interfacing Projects

This directory contains various projects demonstrating how to interface LEDs with the ARM7TDMI-S based LPC2148 microcontroller. The projects are written in bare-metal C using the Keil uVision IDE and cover different patterns of LED blinking using the General Purpose Input/Output (GPIO) pins.

## Hardware Overview
The LPC2148 has two 32-bit GPIO ports: `PORT0` and `PORT1`. 
The pins on Port 0 are used in these examples.
To control an LED:
1. The direction of the GPIO pin must be set as an output using the `IODIR0` register.
2. To turn ON the LED (assuming it's connected in active-high configuration or common cathode), set the corresponding pin HIGH using the `IOSET0` register.
3. To turn OFF the LED, set the corresponding pin LOW using the `IOCLR0` register.

## Registers Used
- `IODIR0` (GPIO Port 0 Direction Register): Used to configure port pins as inputs (0) or outputs (1).
- `IOSET0` (GPIO Port 0 Output Set Register): Writing '1' to a bit sets the corresponding pin to HIGH. Writing '0' has no effect.
- `IOCLR0` (GPIO Port 0 Output Clear Register): Writing '1' to a bit clears the corresponding pin to LOW. Writing '0' has no effect.

## Projects Included

### 1. `LED_blink`
A simple project that blinks an LED connected to `P0.0`.
- It configures `P0.0` to `P0.3` as outputs.
- It repeatedly sets `P0.0` high, delays, and then sets it low using `IOSET0` and `IOCLR0`.

### 2. `alternative`
Blinks LEDs connected to `P0.0`, `P0.1`, `P0.4`, and `P0.5` in an alternating pattern with `P0.2`, `P0.3`, `P0.6`, `P0.7`.
- It uses the hexadecimal values `0x33` (Binary: `0011 0011`) and `0xCC` (Binary: `1100 1100`) to toggle the pins alternately.

### 3. `odd_even`
Blinks LEDs in an odd and even pattern on Port 0 pins 0 to 7.
- Sets alternating odd pins HIGH using `0x55` (Binary `0101 0101`).
- Sets alternating even pins HIGH using `0xAA` (Binary `1010 1010`).

### 4. `shifting`
Creates a shifting pattern by toggling two sets of 4 pins (nibbles) alternately.
- Turns ON pins `P0.0` to `P0.3` using `0x0F` (Binary `0000 1111`).
- Turns ON pins `P0.4` to `P0.7` using `0xF0` (Binary `1111 0000`).

### 5. `one_by_one`
Demonstrates turning on LEDs connected to pins `P0.0` to `P0.7` one after another sequentially.
- Cycles through values `0x01`, `0x02`, `0x04`, `0x08`, `0x10`, `0x20`, `0x40`, and `0x80`.

## Delay Implementation
All projects use a simple software delay loop `void delay()` nested with `for` loops to create a visible time gap between state changes. The execution time of this delay depends on the system clock frequency (CCLK).
