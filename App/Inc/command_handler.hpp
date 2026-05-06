#pragma once

class ICommandHandler {
public:
    virtual ~ICommandHandler() = default;

    virtual void setLed(bool on) = 0;
    virtual void setPump(bool on) = 0;
    virtual void printStatus() = 0;
};
