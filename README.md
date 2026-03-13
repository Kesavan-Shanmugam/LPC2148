# LPC2148 Bare-Metal C Projects Repository

This repository contains a collection of fundamental embedded C programming examples and driver implementations for the **NXP LPC2148** microcontroller, based on the **ARM7TDMI-S** CPU.

These projects were created using **Keil uVision** and demonstrate how to initialize and interface various hardware peripherals and communication protocols by directly manipulating memory-mapped registers (**bare-metal programming**).

---

# Learning Roadmap (Basic → Advanced)

The repository is organized in a **step-by-step embedded learning path**, starting from basic GPIO control and gradually moving toward timers, analog peripherals, and serial communication protocols.

---

## 1. LED
Basic GPIO output examples demonstrating LED blinking, flashing patterns, and shifting.

---

## 2. SWITCH
GPIO input handling using push buttons and triggering outputs based on logical conditions.

---

## 3. 7 SEGMENT
Driving single and multiplexed multi-digit common anode 7-segment displays.

---

## 4. TIMER
Creating precise hardware-based delays using the 32-bit Timer/Counter modules.

---

## 5. LCD
Driver code for a standard **16x2 HD44780-compatible LCD** using 8-bit interface mode.

---

## 6. ADC
Initializing the **10-bit Analog-to-Digital Converter** and reading analog sensor values.

---

## 7. DAC
Using the **10-bit Digital-to-Analog Converter** to generate analog output voltages.

---

## Communication Protocols

### 8. UART0
Polling-based serial communication using the **Universal Asynchronous Receiver-Transmitter**.

### 9. I2C
Master transmitter and receiver implementations for the **I²C protocol**, commonly used for EEPROM or sensor communication.

### 10. SPI
Master full-duplex communication using the **SPI bus** for interfacing synchronous serial devices.

---

## System Configuration

### 11. PLL
Configuration of the **Phase Locked Loop (PLL)** to increase the system clock (`CCLK`) up to **60 MHz**.

---

# Repository Structure
