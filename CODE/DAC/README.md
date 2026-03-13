# LPC2148 DAC (Digital to Analog Converter) Interfacing

This directory contains a project demonstrating how to use the 10-bit Digital-to-Analog Converter (DAC) built into the ARM7TDMI-S based LPC2148 microcontroller.

## Hardware Overview
The LPC2148 features a single 10-bit DAC.
- **Output Pin**: The analog output is available on pin `P0.25` (labeled as `AOUT`).
- **Resolution**: 10-bit, meaning it can generate 1024 discrete voltage levels between $V_{SSA}$ and $V_{REF}$.

## Key Registers Used
1. **`DACR` (D/A Converter Register)**: This is a read/write register that contains the digital value to be converted to an analog voltage.

## Project Analysis (`DAC.c`)
The project contains a very basic loop intended to generate an analog signal (like a ramp or sawtooth wave) on the `AOUT` pin.
```c
int k;
for(k=0; k<0xffffffff; k++)
{
    DACR=k;
}
DACR=0X00000000;
delay();
```

### Important Notes on the Code
There are a couple of functional bugs/misunderstandings in the provided `DAC.c` code:
1. **Missing PINSEL Configuration**: The code does not use the `PINSEL1` register to select the `AOUT` function for pin `P0.25`. By default, `P0.25` acts as a GPIO pin, so no analog voltage will be output unless `PINSEL1` is configured correctly (e.g., `PINSEL1 |= (2<<18)`).
2. **Incorrect `DACR` Value Range**: The loop goes up to `0xFFFFFFFF`, but `DACR` expects the 10-bit value to be placed in bits 6 to 15. The `VALUE` field (bits 15:6) determines the output. Writing a raw integer `k` directly into `DACR` without shifting it horizontally (`DACR = (k << 6)`) and limiting `k` to 1023 (0x3FF) means the output will behave erratically as other control bits (like the BIAS bit) in the register are corrupted.
