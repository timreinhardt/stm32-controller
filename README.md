# STM32 Controller

Small STM32-based controller project created
Tests run on host to allow fast iteration without hardware.

## Overview

Project models a simple controller with:
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
- Tests run on host 

---

## Next
- integrate with STM32 hardware  
- move to C++
- abc
