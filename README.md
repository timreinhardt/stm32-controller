# L476_UART_TEST

## Overview

STM32L476 embedded project refreshed around a cleaner C++ architecture for onboard debugging, UART command handling, and hardware validation.

### Current focus:
- `controller.cpp` → Main control layer
- `serial_command_interface.cpp` → UART command parsing
- `command_handler.hpp` → Hardware command abstraction
- STM32CubeIDE → Build / flash / onboard debug
- Makefile → Host-side C++ unit testing

---

# Project Structure

    L476_UART_TEST/
    ├── App/
    │   ├── Inc/
    │   │   ├── command_handler.hpp
    │   │   ├── controller.hpp
    │   │   ├── pump_controller.hpp
    │   │   └── serial_command_interface.hpp
    │   │
    │   └── Src/
    │       ├── controller.cpp
    │       └── serial_command_interface.cpp
    │
    ├── Core/
    │   └── Src/
    │       └── main.c
    │
    ├── tests/
    │   └── test_pump_controller.cpp
    │
    └── Makefile

---

# Current Status

## Working:
- Flashing firmware to STM32 board
- ST-LINK debugging + stepping through code
- Breakpoints / live code execution validation
- UART command parsing and responses
- Blue hardware button input
- Green onboard LED output
- LED toggle state logic
- Host-side C++ unit test builds

### Hardware / software validation:

    FLASHING      : PASS
    DEBUG/STEP    : PASS
    UART          : PASS
    BUTTON INPUT  : PASS
    LED OUTPUT    : PASS
    COMMAND PARSE : PASS

---

# UART Usage

Connect via:

    screen /dev/tty.usbmodemXXXX 115200

### Available commands:

    HELP
    STATUS
    LED ON
    LED OFF
    PUMP ON
    PUMP OFF

---

# Makefile Unit Testing

## Run examples:

    make test_cpp
    make test_cpp_full
    make clean

---

# Next Steps

1. ISR integration  
2. Real pump GPIO mapping  
3. Expanded STATUS diagnostics  
4. Controller mode architecture  
