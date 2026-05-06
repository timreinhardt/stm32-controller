#include "controller.hpp"

class Controller {
public:
    void init() {
        counter_ = 0;
    }

    void update() {
        counter_++;
    }

private:
    int counter_ = 0;
};

static Controller controller;

extern "C" void Controller_Init(void) {
    controller.init();
}

extern "C" void Controller_Update(void) {
    controller.update();
}
