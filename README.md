# STM32 Controller

Small STM32-based controller project put together as a quick refresher on embedded structure and tooling ahead of getting hands-on with hardware.
Tests run on host (macOS/Linux) to allow fast iteration without hardware.
---

## Overview

The project models a simple controller with:
- a basic state machine (IDLE / RUNNING / FAULT)
- command parsing separated from behaviour
- a small configuration layer (e.g. rate)
- host-side tests for quick iteration
- a simple threading demo

---

## Structure

App/
  Src/
    app.c
    app_cmd.c
    app_state.c

Core/        (STM32Cube generated)
Drivers/     (HAL / CMSIS)

tests/
  unit/
  concurrency/

---

## Running Tests

From the `tests/` folder:

make run      # app/state tests  
make cmd      # command tests  
make matrix   # state combinations  
make thread   # thread demo  

---

## Notes

- Written in C as a quick refresher  
- Structured to keep application logic separate from STM32/HAL code  
- Tests run on host (Mac) to keep iteration fast  

---

## Next

- add event queue  
- introduce BSP layer  
- integrate with STM32 hardware  
- move toward C++  
