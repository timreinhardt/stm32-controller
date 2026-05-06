# =========================
# Host-side Unit Test + STM32 Logic Makefile
# Cleaned for current C++ structure
# Project root:
# L476_UART_TEST/Makefile
# =========================

CC  = gcc
CXX = clang++

# =========================
# Project Paths
# =========================
APP_INC   = App/Inc
APP_SRC   = App/Src
TEST_DIR  = tests

# =========================
# Common Flags
# =========================
COMMON_WARN  = -Wall -Wextra
COMMON_DEFS  = -DUNIT_TEST
COMMON_INC   = -I$(APP_INC)

CFLAGS   = $(COMMON_DEFS) $(COMMON_WARN) -std=c11 $(COMMON_INC)
CXXFLAGS = $(COMMON_DEFS) $(COMMON_WARN) -std=c++14 $(COMMON_INC)

# =========================
# Current C++ Unit Tests
# =========================

# Header-only pump controller
test_cpp:
	$(CXX) $(CXXFLAGS) \
	$(TEST_DIR)/test_pump_controller.cpp \
	-o test_pump_controller
	./test_pump_controller


# Full project logic test
test_cpp_full:
	$(CXX) $(CXXFLAGS) \
	$(APP_SRC)/controller.cpp \
	$(APP_SRC)/serial_command_interface.cpp \
	$(TEST_DIR)/test_pump_controller.cpp \
	-o test_pump_controller
	./test_pump_controller


# =========================
# Convenience
# =========================

all_tests: test_cpp



# =========================
# Clean
# =========================

CLEAN_FILES = \
	test_pump_controller

clean:
	rm -f $(CLEAN_FILES)