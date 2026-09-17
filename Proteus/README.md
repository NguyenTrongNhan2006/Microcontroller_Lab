# Proteus 8.10 Simulation Setup

## Target Microcontroller
- **MCU**: STM32F103C6
- **Operating Voltage**: +3.3V
- **Power connections**:
  - `VDDA` connected to `+3.3V` (Terminal -> Power with string property `+3.3V`)
  - `VSSA` connected to `GND` (Terminal -> Ground)

## Components List
1. **STM32F103C6**: Microcontroller Unit
2. **LED-RED, LED-YELLOW, LED-GREEN**: Animated LEDs (Active LOW: cathode connected to STM32 GPIO, anode to +3.3V)
3. **7SEG-COM-ANODE**: 7-segment display (Common anode to +3.3V, pins a..g to PB0..PB6)
4. **Resistors**: 220Ω / 330Ω current-limiting resistors for LEDs

## Pin Mapping
| Pin Name | Function / Component | Note |
|---|---|---|
| PA4 - PA15 | 12 Clock LEDs (12 o'clock down to 11 o'clock) | Exercises 6 - 10 |
| PA5 | LED-RED (Traffic Light / Blinky) | Exercises 1 - 3 |
| PA6 | LED-YELLOW (Traffic Light) | Exercises 1 - 3 |
| PA7 | LED-GREEN (Traffic Light) | Exercises 2 - 3 |
| PB0 - PB6 | 7SEG-COM-ANODE (Segments a, b, c, d, e, f, g) | Exercises 4 - 5 |

## Loading HEX File in Proteus
1. Double click on the **STM32F103C6** component in Proteus.
2. In **Program File**, browse to your compiled `.hex` file (e.g. `Debug/Microcontroller_Lab1.hex`).
3. Set **Crystal Frequency** to `8MHz` or default.
4. Click **OK**, then press **Play** (F12 or bottom-left play button) to run simulation.
