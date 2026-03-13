# LPC2148 Switch Interfacing Projects

This directory contains projects demonstrating how to interface tactile switches (push buttons) as digital inputs with the ARM7TDMI-S based LPC2148 microcontroller. The projects use input from switches to control the state of LEDs.

## Hardware Overview
To read the state of a switch connected to a GPIO pin:
1. The direction of the GPIO pin must be configured as an input using the `IODIR0` register.
2. The current logical state (HIGH or LOW) of the pin can be read from the `IOPIN0` register.
3. In these examples, the switches are assumed to be connected in an **active-low** configuration (connecting the pin to ground when pressed, with an internal or external pull-up resistor keeping it high otherwise).

## Registers Used
- `IODIR0` (GPIO Port 0 Direction Register): Used to set pins as inputs (bit = 0) or outputs (bit = 1).
- `IOPIN0` (GPIO Port 0 Pin Value Register): Reflects the current state of the port pins, regardless of direction. Used to read the switch state.
- `IOSET0` & `IOCLR0`: Used to control the output LEDs.

## Projects Included

### 1. `led_on` (led_on_button.c)
A basic example of controlling one LED with one switch.
- **Input:** Switch on `P0.1`.
- **Output:** LED on `P0.0`.
- **Logic:** If the switch is pressed (`IOPIN0 & (1<<1)` is 0), the LED is turned ON using `IOSET0 = 1<<0`. Otherwise, it is turned OFF using `IOCLR0 = 1<<0`.

### 2. `task_1`
A more complex logic scenario using multiple switches and logical operators (OR, AND) to control multiple LEDs.
- **Inputs:** Switches on `P0.0` to `P0.5`.
- **Outputs:** LEDs on `P0.6` to `P0.9`.
- **Logic Rules:**
  - If `Sw0` is pressed: Turn ON LED `P0.6`, turn OFF `P0.7`, `P0.8`, `P0.9`.
  - Else if `Sw1` OR `Sw2` is pressed: Turn ON LEDs `P0.6`, `P0.7`, turn OFF `P0.8`, `P0.9`.
  - Else if `Sw3` AND `Sw4` are pressed: Turn ON LEDs `P0.6`, `P0.7`, `P0.8`, turn OFF `P0.9`.
  - Else if `Sw5` is pressed: Turn ON all LEDs (`P0.6` to `P0.9`).
  - Default: Turn OFF all LEDs.

### 3. `task_2`
A scenario mapping individual switches to individual LEDs with an exception.
- **Inputs:** Switches on `P0.0` to `P0.3`.
- **Outputs:** LEDs on `P0.4` to `P0.6`.
- **Logic Rules:**
  - If `Sw0` is pressed: Turn ON LED `P0.4`, turn OFF others.
  - Else if `Sw1` is pressed: Turn ON LED `P0.5`, turn OFF others.
  - Else if `Sw2` is pressed: Turn ON LED `P0.6`, turn OFF others.
  - Else if `Sw3` is pressed: Turn OFF all LEDs.

## Note on IODIR0 Configuration
In `task_1.c` and `task_2.c`, the lines setting `IODIR0` use a mix of assignment (`=`) that overwrites previous values. For example, in `task_1.c`:
```c
IODIR0 = ~(1<<0)|(1<<1)|...
IODIR0 = (1<<6)|(1<<7)|...
```
The second line overwrites the first. The intention is to set pins 6-9 as outputs (1) and everything else as inputs (0).
