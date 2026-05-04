# STM32 Controller

Ongoing practical STM32 / embedded development project focused on progressive refreshers, initially host-side testing, then real hardware integration.

**Latest:** Host-side Makefile test framework + UART command parser added before full board UART validation.

NB Pending HW

Initial STM32 project generated via STM32CubeMX / STM32CubeIDE for the NUCLEO-L476RG development board, then progressively extended with custom application and hardware validation layers.

---

# Repository Structure

```text
App/
 ├── Inc/
 │    ├── app.h            (host/laptop only - Makefile tests)
 │    ├── app_cmd.h        (host command parser)
 │    ├── app_state.h      (host state machine)
 │    ├── app_uart.h       (UART interface)
 │    ├── app_uart_cmd.h   (UART enum + command text table)
 │    └── app_hw.h         (STM32 dev board / HAL)
 │
 └── Src/
      ├── app.c            (host/laptop only - Makefile tests)
      ├── app_cmd.c
      ├── app_state.c
      ├── app_uart.c       (UART parser + STM32 UART task)
      └── app_hw.c         (STM32 dev board / HAL)

Core/      (CubeMX / STM32 generated)
Drivers/   (HAL / CMSIS)

tests/
 ├── concurrency/
 │    └── thread_demo.c
 ├── Makefile
 └── unit/
      ├── test_app.c
      ├── test_cmd.c
      ├── test_state_matrix.c
      └── test_uart_cmd.c
```

---

# Current Development Modes

## Local / Host-side (`/tests` Makefile)
Fast laptop-side validation without flashing STM32:

```bash
make run
make cmd
make matrix
make thread
make test_uart
```

### Purpose:
- `make run` → app/state tests
- `make cmd` → host command parser
- `make matrix` → state transitions
- `make thread` → pthread refresher
- `make test_uart` → UART parser / enum / case handling

---

## STM32 / CubeIDE Build
Used for:
```text
GPIO
Button + LED
HAL
UART hardware integration
```

---

# App Layer Overview

## app_hw.c
```text
USER button + LD2 LED GPIO validation
Debounced button press
LED toggle per press
```

## app_uart.c
```text
UART command parsing
Case-insensitive input
PING
HELP
STATUS
LED_ON
LED_OFF
LED_TOGGLE
```

---

# STM32 Hardware Test: USER Button + LD2 LED

Simple NUCLEO-L476RG board validation.

## Purpose
Confirm:
- CubeMX pin config
- HAL GPIO
- Button input
- LED output
- Debounce
- Build chain

---

# Board Mapping

```text
B1 USER button = PC13
LD2 green LED  = PA5
RESET          = NRST hardware reset
```

---

# Build Requirements

## STM32 Hardware Build:
Exclude host-only files:
```text
App/Inc/app.h
App/Inc/app_cmd.h
App/Inc/app_state.h

App/Src/app.c
App/Src/app_cmd.c
App/Src/app_state.c
```

Keeps STM32 build focused on hardware validation + UART integration.

---

## Local Makefile Tests:
Uses host-side files for rapid development without STM32 hardware.

---

# Behaviour

```text
Press USER once → LED toggle
UART over USB-COM → command parser
```

---

# Current Status

```text
CubeMX STM32 base project
GPIO validated
Button debounce
LED toggle
Host test framework
UART parser architecture
UART unit tests passing
```
