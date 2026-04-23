# STM32 Embedded Controller Example

Small embedded controller-style project created to refresh low-level embedded patterns and explore architecture ahead of working with STM32 hardware.

Focus is on structure, testability, and workflow, not hardware integration (yet).

---

## Overview

This project models a simple embedded controller with:
- Event-driven state machine
- Command parsing layer
- Application/configuration layer
- Host-based unit testing
- Basic concurrency demo (threads)

---

## Architecture

Input (UART / test)
        ↓
app_cmd        → parses commands
        ↓
app_state      → enforces behaviour (state machine)
        ↓
app            → stores configuration (e.g. rate)

### State Machine

States:
- IDLE
- RUNNING
- FAULT

Events:
- START
- STOP
- FAULT_DETECTED
- RESET

Transitions handled in:
App/Src/app_state.c

---

## Project Structure

App/
  Inc/
  Src/
    app.c
    app_cmd.c
    app_state.c

Core/        (STM32Cube generated code)
Drivers/     (HAL / CMSIS)

tests/
  unit/
    test_app.c
    test_cmd.c
    test_state_matrix.c
  concurrency/
    thread_demo.c
  Makefile

---

## Running Tests (Host)

From the tests/ directory:

make run      # app/state tests
make cmd      # command tests
make matrix   # state/event coverage
make thread   # concurrency demo

---

## Concurrency Demo

Basic producer/consumer example using:
- pthread_mutex
- pthread_cond

File:
tests/concurrency/thread_demo.c

---

## Toolchain

- STM32CubeMX
- STM32CubeIDE
- GCC/Clang (host testing)

---

## Current Status

- No hardware integration yet
- Logic fully testable on host
- Structure prepared for:
  - BSP layer
  - RTOS integration
  - event-driven architecture

---

## Next Steps

- Introduce event queue
- Add BSP layer
- Integrate with STM32 hardware
- Transition toward C++

---

## Notes

This is a learning / preparation project, not production code.

Focus areas:
- separation of concerns
- embedded architecture patterns
- testability without hardware
