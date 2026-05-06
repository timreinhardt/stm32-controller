# L476_UART_TEST

## Overview

STM32L476 embedded project refresshers  

### Current focus:
- `controller.cpp` → Main C++ control layer
- UART / VCP → Runtime debug + command interface
- STM32CubeIDE → Build / flash / debug
- Host-side Makefile → Unit testing

---

# Project Structure

```text
L476_UART_TEST/
├── App/
│   ├── Inc/
│   │   ├── controller.hpp
│   │   └── pump_controller.hpp
│   └── Src/
│       ├── controller.cpp (LED and button)
│       ├── app.c (initial c test - delete)
│       ├── app_cmd.c
│       └── app_state.c
│
├── Core/
│   └── Src/
│       └── main.c
│
├── tests/
│   ├── test_pump_controller.cpp
│   └── unit/
│       ├── test_app.c
│       ├── test_cmd.c
│       └── test_uart_cmd.c
│
└── Makefile (unit tests)
```

---

# Current Status

## Working:
- STM32 build + flash
- ST-LINK debug
- `controller.cpp` LED/button logic
- UART over USB (`screen /dev/tty.usbmodemXXXX 115200`)
- Host-side unit testing via Makefile

---

# Makefile Unit Testing

## Run examples:

```bash
make test_cpp
make run
make cmd
make test_uart
make clean
```

---

# Architecture Direction

## Legacy:
- `app.c`
- `app_cmd.c`
- `app_state.c`

## Moving toward:
- `controller.cpp`
- modular C++ logic
- hardware abstraction
- TDD / SOLID

---

# Immediate Next Steps

1. Expand `controller.cpp`
2. ISR

---
