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

```text
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

---

# Makefile Unit Testing

## Run examples:

```bash
make test_cpp
make all
make cmd
make clean
```

---


#  Next Steps

1. ISR
2. rework

---
