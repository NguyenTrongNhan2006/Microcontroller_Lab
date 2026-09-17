# Microcontroller - Lab 1: LED Animations

**Ho Chi Minh City University of Technology (HCMUT - BKU)**  
**Department of Computer Engineering**  
**Course**: Microcontroller / Vi xử lý  
**Instructor**: Dr. Le Trong Nhan  

---

## 📋 Overview
This repository contains the source code templates and implementation structure for **Lab 1: LED Animations**, covering all 10 exercises described in the official course lab manual.

- **Target MCU**: `STM32F103C6` (ARM Cortex-M3)
- **Toolchain**: STM32CubeIDE (v1.7.0+)
- **Simulation**: Proteus 8.10 SP0 Professional

---

## 📁 Repository Structure

```
Microcontroller_Lab1/
├── Core/
│   ├── Inc/
│   │   ├── main.h             # Master pin definitions and includes
│   │   ├── exercise1.h        # Exercise 1 header
│   │   ├── exercise2.h        # Exercise 2 header
│   │   ├── exercise3.h        # Exercise 3 header
│   │   ├── exercise4.h        # Exercise 4 header (display7SEG prototype)
│   │   ├── exercise5.h        # Exercise 5 header
│   │   ├── exercise6.h        # Exercise 6 header
│   │   ├── exercise7.h        # Exercise 7 header (clearAllClock prototype)
│   │   ├── exercise8.h        # Exercise 8 header (setNumberOnClock prototype)
│   │   ├── exercise9.h        # Exercise 9 header (clearNumberOnClock prototype)
│   │   └── exercise10.h       # Exercise 10 header
│   └── Src/
│       ├── main.c             # System initialization and exercise runner
│       ├── exercise1.c        # Exercise 1 implementation
│       ├── exercise2.c        # Exercise 2 implementation
│       ├── exercise3.c        # Exercise 3 implementation
│       ├── exercise4.c        # Exercise 4 implementation (display7SEG)
│       ├── exercise5.c        # Exercise 5 implementation
│       ├── exercise6.c        # Exercise 6 implementation
│       ├── exercise7.c        # Exercise 7 implementation (clearAllClock)
│       ├── exercise8.c        # Exercise 8 implementation (setNumberOnClock)
│       ├── exercise9.c        # Exercise 9 implementation (clearNumberOnClock)
│       └── exercise10.c       # Exercise 10 implementation
├── Exercise_1/                # Standalone project files for Exercise 1
│   └── main.c
├── Exercise_2/                # Standalone project files for Exercise 2
│   └── main.c
├── Exercise_3/                # Standalone project files for Exercise 3
│   └── main.c
├── Exercise_4/                # Standalone project files for Exercise 4
│   └── main.c
├── Exercise_5/                # Standalone project files for Exercise 5
│   └── main.c
├── Exercise_6/                # Standalone project files for Exercise 6
│   └── main.c
├── Exercise_7/                # Standalone project files for Exercise 7
│   └── main.c
├── Exercise_8/                # Standalone project files for Exercise 8
│   └── main.c
├── Exercise_9/                # Standalone project files for Exercise 9
│   └── main.c
├── Exercise_10/               # Standalone project files for Exercise 10
│   └── main.c
├── Proteus/                   # Proteus simulation schematics and notes
│   └── README.md
├── .gitignore
└── README.md
```

---

## 🛠️ Summary of Exercises

### Section 4.1 - Exercise 1: 2 LEDs Alternating Blinky
- **Pins**: PA5 (`LED-RED`), PA6 (`LED-YELLOW`).
- **Function**: The state of the two LEDs alternates every 2 seconds.
- **Circuit**: Active LOW (Cathode connected to STM32 pin, Anode connected to +3.3V).

### Section 4.2 - Exercise 2: Traffic Light Simulation
- **Pins**: PA5 (`LED-RED`), PA6 (`LED-YELLOW`), PA7 (`LED-GREEN`).
- **Timing**: 
  - RED: 5 seconds
  - GREEN: 3 seconds
  - YELLOW: 2 seconds

### Section 4.3 - Exercise 3: 4-Way Traffic Light
- **Components**: 12 LEDs arranged to simulate a 4-way intersection (North-South & East-West).
- **Behavior**: Coordinated traffic light cycles ensuring safe intersections.

### Section 4.4 - Exercise 4: 7-Segment Display (7SEG-COM-ANODE)
- **Pins**: PB0 to PB6 corresponding to segments `a`, `b`, `c`, `d`, `e`, `f`, `g`.
- **Logic**: Active LOW (logic 0 turns ON the segment, logic 1 turns OFF).
- **Required Function**:
  ```c
  void display7SEG(int num);
  ```
  Displays digits `0` through `9`.

### Section 4.5 - Exercise 5: 4-Way Traffic Light with Countdown
- **Function**: Re-uses `display7SEG()` to show real-time countdown seconds synchronized with the traffic light signals.

### Section 4.6 - Exercise 6: Analog Clock - 12 LEDs Connection Test
- **Pins**: PA4 to PA15 representing 12 clock hour positions.
- **Function**: Turn on each LED in sequence to verify all connections.

### Section 4.7 - Exercise 7: Function clearAllClock()
- **Required Function**:
  ```c
  void clearAllClock(void);
  ```
- **Function**: Turns off all 12 clock LEDs simultaneously.

### Section 4.8 - Exercise 8: Function setNumberOnClock()
- **Required Function**:
  ```c
  void setNumberOnClock(int num);
  ```
- **Input**: `num` from 0 to 11.
- **Function**: Turns ON the LED at clock position `num`.

### Section 4.9 - Exercise 9: Function clearNumberOnClock()
- **Required Function**:
  ```c
  void clearNumberOnClock(int num);
  ```
- **Input**: `num` from 0 to 11.
- **Function**: Turns OFF the LED at clock position `num`.

### Section 4.10 - Exercise 10: Analog Clock Full Integration
- **Function**: Uses the 12 LEDs to display a complete analog clock with Hour, Minute, and Second hands.
- **Constraint**: At any given time, only **3 LEDs** are turned ON.

---

## 🚀 How to Build & Simulate

### 1. STM32CubeIDE
1. Open **STM32CubeIDE** and import the project or copy the exercise files into your workspace.
2. Enable Intel Hex output:
   - Right click Project -> **Properties** -> **C/C++ Build** -> **Settings** -> **MCU Post build outputs**.
   - Check **Convert to Intel Hex file (-O ihex)**.
3. Build the project (**Ctrl + B**). The `.hex` file will be generated in the `Debug/` folder.

### 2. Proteus Simulation
1. Launch **Proteus 8.10 SP0** with Administrator privileges.
2. Open the schematic in the `Proteus/` folder or create one following the lab manual guide.
3. Double-click the STM32F103C6 MCU, select the generated `.hex` file in **Program File**.
4. Press **Run** (F12) to simulate.

---

## 👤 Author
- **Student**: Nguyen Trong Nhan
- **GitHub**: [@NguyenTrongNhan2006](https://github.com/NguyenTrongNhan2006)
- **Repository**: [https://github.com/NguyenTrongNhan2006/Microcontroller_Lab1](https://github.com/NguyenTrongNhan2006/Microcontroller_Lab1)
