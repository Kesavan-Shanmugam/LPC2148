# LPC2148 Timer Interfacing

This directory contains projects demonstrating how to use the hardware timers on the ARM7TDMI-S based LPC2148 microcontroller. Currently, it includes an example of using Timer 0 to create precise delays for blinking an LED.

## Hardware Overview
The LPC2148 has two 32-bit Timer/Counters: Timer 0 and Timer 1.
They can be used for timing internal events (via the peripheral clock) or counting external events.

## Key Registers Used (Timer 0)
1. **`T0CTCR` (Count Control Register)**: Selects whether the timer operates as a Timer (driven by PCLK) or a Counter.
2. **`T0TCR` (Timer Control Register)**: Used to enable (start), disable (stop), and reset the timer.
3. **`T0PR` (Prescale Register)**: Contains the 32-bit value that dictates the resolution of the timer. The Timer Counter (`T0TC`) is incremented every time the Prescale Counter (`T0PC`) reaches the value in `T0PR`.
4. **`T0TC` (Timer Counter Register)**: The 32-bit register that is incremented when the prescaler matches.

## Project Analysis (`led_timer0.c`)

This project implements a precise delay function using Timer 0 to blink an LED on `P0.0`.

### Timer Configuration (`timer()` function)
```c
T0CTCR = 0x00;        // Set to Timer mode (every rising PCLK edge)
T0TCR  = 0x00;        // Disable the timer initially
T0PR   = 59999;       // Set Prescale value
T0TCR  = 0x02;        // Reset the Timer Counter and Prescale Counter
T0TCR  = 0x01;        // Enable the timer
while(T0TC < 10);     // Wait until the Timer Counter reaches 10
T0TCR  = 0x00;        // Disable timer
T0TC   = 0;           // Reset counter manually (Though T0TCR=0x02 should do this)
```

### Understanding the Delay
The delay generated depends on the Peripheral Clock (`PCLK`).
Looking at the `pll()` function within the code:
- Multiplier = 5 (`PLL0CFG = 0x24`), `CCLK` = $12 MHz \times 5 = 60 MHz$.
- `VPBDIV = 0x01` means `PCLK` = `CCLK` = 60 MHz.
- So, 1 timer tick = $1 / 60,000,000$ seconds.

The prescaler `T0PR` is set to 59,999. Notice that prescale counter increments from 0 to `T0PR`, so it takes 60,000 PCLK cycles for the main counter `T0TC` to increment by 1.
- Time for 1 `T0TC` increment = $60,000 \times (1 / 60,000,000) = 1$ millisecond.

The `while(T0TC < 10);` loop waits for 10 increments of `T0TC`, thus creating a **10 millisecond delay**.

### LED Blinking
The `main()` function simply sets `P0.0` HIGH, calls the 10ms `timer()` delay, sets `P0.0` LOW, and calls the delay again, repeating infinitely. *Note: 10ms is very fast, appearing as a slightly dim, continuously ON LED to the human eye rather than a distinct blink.*
