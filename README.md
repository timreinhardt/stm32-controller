# STM32 Controller

Ongoing practical STM32 / embedded development project focused on progressive refreshers, initially host-side testing, then real hardware integration.

NB Pending HW

Initial STM32 project generated via STM32CubeMX / STM32CubeIDE for the NUCLEO-L476RG development board, then progressively extended with custom application and hardware validation layers.

---

# Repository Structure

```text
App/
 ├── Inc/
 │    ├── app.h        (host/laptop only - Makefile tests)
 │    ├── app_cmd.h
 │    ├── app_state.h
 │    └── app_hw.h     (STM32 dev board / HAL)
 │
 └── Src/
      ├── app.c        (host/laptop only - Makefile tests)
      ├── app_cmd.c
      ├── app_state.c
      └── app_hw.c     (STM32 dev board / HAL)

Core/
Drivers/
tests/
```

---

# App Layer Overview

## STM32 Hardware
### app_hw.c

```text
USER button + LD2 LED GPIO validation
```

---

## Host-Side Testing (Laptop)

inital iteration without STM32 hardware.

## From `/tests`:

```bash
make run
make cmd
make matrix
make thread
```

### Purpose:
- `make run` → app/state tests
- `make cmd` → command parser
- `make matrix` → state transitions
- `make thread` → pthread refresher

---

# Concurrency Demo

## Shared:

```text
mutex
condition variable
shared count
```

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

# Behaviour

```text
Press USER once  → LED toggle
```


# Build Requirements

Exclude laptop files:
App/Inc/app.h
App/Inc/app_cmd.h
App/Inc/app_state.h

App/Src/app.c
App/Src/app_cmd.c
App/Src/app_state.c

keeps  STM32 hardware test focused only on USER button + LED validation while excluding host-side logic and test architecture.
```





