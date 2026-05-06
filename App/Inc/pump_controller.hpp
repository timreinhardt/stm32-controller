// =============================
// PUMP CONTROLLER
// Purpose:
// Contains pump control logic
// Pure C++
// No STM32 hardware needed
// =============================

#pragma once

enum class PumpCommand {
    Off,   // Pump should be OFF
    On     // Pump should be ON
};


class PumpController {

public:
    // ------------------------------------------------
    // Main logic function
    //
    // Input:
    // pressureBar = current system pressure
    //
    // Output:
    // Returns current command state
    // ------------------------------------------------
    PumpCommand update(float pressureBar) {

        // --------------------------------------------
        // If pressure too LOW
        // Start pump
        // --------------------------------------------
        if (pressureBar < 4.0f) {
            command_ = PumpCommand::On;
        }

        // --------------------------------------------
        // If pressure too HIGH
        // Stop pump
        // --------------------------------------------
        if (pressureBar > 6.0f) {
            command_ = PumpCommand::Off;
        }

        // --------------------------------------------
        // If pressure between 4 and 6:
        // No change
        // Holds previous state
        //
        // hysteresis:
        // prevents rapid ON/OFF switching
        // --------------------------------------------

        // Return current state
        return command_;
    }



    // ------------------------------------------------
    // Getter function
    // ------------------------------------------------
    PumpCommand command() const {
        return command_;
    }



private:
    // ------------------------------------------------
    // PRIVATE = protected internal state
    //
    // Stores current pump command
    //
    // Starts OFF by default
    // ------------------------------------------------
    PumpCommand command_ = PumpCommand::Off;
};
