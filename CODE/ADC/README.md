# LPC2148 ADC (Analog to Digital Converter) Interfacing

This directory contains a project demonstrating how to use the 10-bit Analog-to-Digital Converter (ADC) built into the ARM7TDMI-S based LPC2148 microcontroller.

## Hardware Overview
The LPC2148 features two 10-bit successive approximation ADCs (ADC0 and ADC1).
- **ADC0** has 6 channels (multiplexed onto `P0.27` to `P0.30` and `P0.22` to `P0.23`).
- **Resolution**: 10-bit, meaning it converts an analog voltage to a digital value ranging from 0 to 1023 ($2^{10} - 1$).
- **Function Pin Selection**: The GPIO pins must be configured to their alternate ADC function using the `PINSEL` registers.

## Key Registers Used
1. **`PINSEL1`**: Used to select the ADC function for the specific GPIO pin.
2. **`AD0CR` (ADC0 Control Register)**: Selects the channel to be converted, operational mode, clock divider, and initiates the conversion.
3. **`AD0GDR` (ADC0 Global Data Register)**: Contains the 10-bit conversion result and the DONE flag.

## Project Analysis (`ADC.c`)

This project reads an analog value from **Channel 2 of ADC0** (`AD0.2`), which is mapped to pin **`P0.25`** on the LPC2148, and displays the digital equivalent on a 16x2 LCD.

### Initialization & Configuration (`adc_init`)
```c
PINSEL1 |=(1<<24);                 // set bit 24=1
PINSEL1 &=~(1<<25);                // set bit 25=0 (Selects AD0.2 function on P0.25)
AD0CR =(1<<2)|(13<<8)|(1<<21);     // SEL=Channel 2 (bit 2), CLKDIV=13, PDN=1 (Operational)
```

### Reading the ADC Value (`adc_read`)
1. **Start Conversion**: A conversion is initiated by writing `001` to the START bits in `AD0CR`. The code uses `AD0CR |= (1<<24)`.
2. **Wait for Completion**: The code polls the DONE bit (bit 31) in `AD0GDR` to wait until the conversion finishes: `while(!(AD0GDR &(1<<31)));`.
3. **Extract Result**: The 10-bit result is located in bits 6:15 of `AD0GDR`. It shifts the register right by 6 and masks it with `0x03FF` (1023) to extract just the value: `(AD0GDR>>6) & 0x03FF`.

### Display Logic
The project also includes the LCD driver code mentioned in the `CODE/LCD` directory.
It uses `sprintf` to format the integer ADC reading (0-1023) into a string, and then iterates through the string to send each character to the LCD using the `display_data` function.

### PLL Configuration (`pll()`)
Noticeably, this code includes a `pll()` (Phase Locked Loop) configuration block. This sets up the system clock (CCLK) to be multiplied from the external oscillator to ensure fast execution and correct peripheral timings.
