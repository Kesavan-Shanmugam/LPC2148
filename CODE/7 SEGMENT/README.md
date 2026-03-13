# LPC2148 7-Segment Display Interfacing Projects

This directory contains projects demonstrating how to interface common anode 7-segment displays with the ARM7TDMI-S based LPC2148 microcontroller. The projects progress from a single-digit display to multiplexed double and four-digit displays.

## Hardware Overview
A 7-segment display consists of seven LEDs arranged in an "8" shape, plus an optional decimal point.
- **Common Anode**: The positive terminals (anodes) of all 8 LEDs are tied together and connected to VCC. To turn ON a specific segment, the corresponding microcontroller pin (connected to the cathode) must be pulled LOW (0).
- **Data Pins**: Pins `P0.0` to `P0.7` are used to drive the individual segments (A, B, C, D, E, F, G, DP).
- **Multiplexing Control Pins**: For multi-digit displays, separate pins are used to select which digit is currently active. Transistors are typically used to switch the common anode of each digit. The control pins (like `P0.8`, `P0.9`, etc.) are pulled LOW to activate a specific digit's transistor.

## Segment Data Mapping
A common array is used across these projects to map decimal numbers (0-9) to the corresponding 8-bit hex values required to light up the correct segments on a common anode display:
```c
// 0x3F = 0, 0x06 = 1, 0x5B = 2, etc. (Note: The values in the code represent the segments to turn ON. 
// Since it uses IOSET for the data, it appears to be treating the segments as Active-High, which implies Common Cathode in the physical setup, or there's an inverting buffer/driver IC in between).
int a[]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
```

## Projects Included

### 1. `SINGLE DIGIT`
Demonstrates driving a single 7-segment display.
- **Example (`0_to_9_print.c`)**: Loops from 0 to 9, passing the value to the array `a[]`, setting the data on `PORT0` using `IOSET0`, delaying, and clearing it.

### 2. `DOUBLE DIGIT`
Demonstrates multiplexing two 7-segment displays.
- **Multiplexing Concept**: Only one digit is turned on at a time. By switching between them very fast (faster than the human eye's refresh rate, persistence of vision), both digits appear to be on simultaneously.
- **Control Pins**: Uses `P0.8` (`0x0100`) and `P0.9` (`0x0200`) as digit select lines.
- **Example (`double_num.c`)**: 
  - Turns on the first digit (`IOSET0=0X00000200`), outputs the data for '3' (`a[3]`), delays, and clears.
  - Turns on the second digit (`IOSET0=0X00000100`), outputs the data for '3', delays, and clears.
  - This displays "33" statically.

### 3. `FOUR DIGIT`
Demonstrates multiplexing four 7-segment displays and creating a counter.
- **Control Pins**: Uses `P0.8`, `P0.9`, `P0.10` (`0x0400`), and `P0.11` (`0x0800`).
- **Logic (`0_to_9999.c`)**: 
  - Loops a counter `k` from 0 to 9999.
  - Slices the number `k` into individual digits (`first` = thousands, `second` = hundreds, `third` = tens, `fourth` = ones).
  - Rapidly multiplexes the four digits by enabling one digit control pin, outputting the respective sliced number via the array, delaying concisely, and repeating for the next digit.
  - *Note*: The code uses a slightly different logic for selection lines. For example, `IOSET0=0X00000700` sets pins 8, 9, 10 HIGH, effectively leaving pin 11 LOW (if it was cleared previously), which might activate the 4th digit in an active-low select configuration.
