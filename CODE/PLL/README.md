# LPC2148 Phase Locked Loop (PLL) Configuration

This directory contains a foundational project demonstrating how to configure the Phase Locked Loop (PLL) on the ARM7TDMI-S based LPC2148 microcontroller. The PLL is essential for bumping up the external crystal oscillator frequency to the highest possible processing frequency for the core.

## Overview
The LPC2148 can operate at a maximum CPU Clock frequency (`CCLK`) of **60 MHz**. Typically, an external 12 MHz crystal is connected to the oscillator pins. The PLL is used to multiply this 12 MHz input up to the required 60 MHz.
The `VPB` (VLSI Peripheral Bus) Clock, or `PCLK`, drives the peripherals (like UART, SPI, Timer) and can be derived from the `CCLK` using the `VPBDIV` register.

## Key Registers
1. **`PLL0CON` (PLL0 Control Register)**: Contains bits to enable (bit 0) and connect (bit 1) the PLL.
2. **`PLL0CFG` (PLL0 Configuration Register)**: Configures the Multiplier (`MSEL`) and the Divider (`PSEL`).
   - `CCLK = M * FOSC`
   - `FCCO = CCLK * 2 * P` (Current Controlled Oscillator frequency, must remain between 156 MHz and 320 MHz).
3. **`PLL0STAT` (PLL0 Status Register)**: Contains the `PLOCK` bit (bit 10), indicating that the PLL has achieved phase lock on the target frequency.
4. **`PLL0FEED` (PLL0 Feed Register)**: A specific sequence (`0xAA` followed by `0x55`) must be written here to commit any changes made to `PLL0CON` or `PLL0CFG`.
5. **`VPBDIV` (VPB Divider Register)**: Determines the `PCLK` frequency relative to `CCLK`.

## Project Analysis (`pll.c`)

The project contains a standard setup sequence function `pll()` that configures `CCLK` to 60 MHz and `PCLK` to 60 MHz based on an assumed 12 MHz external crystal (`FOSC`).

### Logic
```c
PLL0CON = 0x01;       // Enable PLL0 (but don't connect it yet)
PLL0CFG = 0x24;       // Set Multiplier M=5 (0x24 low bits: 00100 = M-1 = 4, so M=5)
                      // Set Divider P=2 (0x24 high bits: 10 = P value 2)
                      // CCLK = 12 * 5 = 60 MHz.
                      // FCCO = 60 * 2 * 2 = 240 MHz (within valid 156-320MHz range).

PLL0FEED = 0xAA;      // Feed sequence part 1
PLL0FEED = 0x55;      // Feed sequence part 2 (applies ENABLE and config)

while(PLL0STAT == (1<<10)); // BUG in the code: It should be waiting FOR the lock bit to be set.
                            // The line `while(!(PLL0STAT & (1<<10)));` is the correct logic as seen in other modules.
                            // The current line `while(PLL0STAT==(1<<10));` wait infinitely IF it locks, which is broken.

PLL0CON = 0x03;       // Enable AND Connect PLL0
PLL0FEED = 0xAA;      // Feed sequence part 1
PLL0FEED = 0x55;      // Feed sequence part 2 (applies CONNECT)

VPBDIV = 0x01;        // Set PCLK = CCLK = 60 MHz
```
*Note: Almost every other project in this repository (e.g. UART, Timer) uses a corrected version of this `pll()` function.*
