# =========================
# Host-side Unit Test + STM32 Logic Makefile
# Single-point config for paths + flags
# Place in project root:
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
UNIT_DIR  = $(TEST_DIR)/unit
CONC_DIR  = $(TEST_DIR)/concurrency

# =========================
# Common Flags
# =========================
COMMON_WARN  = -Wall -Wextra
COMMON_DEFS  = -DUNIT_TEST
COMMON_INC   = -I$(APP_INC)

CFLAGS   = $(COMMON_DEFS) $(COMMON_WARN) -std=c11 $(COMMON_INC)
CXXFLAGS = $(COMMON_DEFS) $(COMMON_WARN) -std=c++14 $(COMMON_INC)

PTHREAD_FLAGS = -pthread


# =========================
# Existing C Tests
# =========================

run:
	$(CC) $(CFLAGS) \
	$(APP_SRC)/app.c \
	$(APP_SRC)/app_state.c \
	$(UNIT_DIR)/test_app.c \
	-o test_app
	./test_app


cmd:
	$(CC) $(CFLAGS) \
	$(APP_SRC)/app.c \
	$(APP_SRC)/app_state.c \
	$(APP_SRC)/app_cmd.c \
	$(UNIT_DIR)/test_cmd.c \
	-o test_cmd
	./test_cmd


matrix:
	$(CC) $(CFLAGS) \
	$(APP_SRC)/app.c \
	$(APP_SRC)/app_state.c \
	$(UNIT_DIR)/test_state_matrix.c \
	-o test_state_matrix
	./test_state_matrix


thread:
	$(CC) $(CFLAGS) \
	$(CONC_DIR)/thread_demo.c \
	-o thread_demo \
	$(PTHREAD_FLAGS)
	./thread_demo


test_uart:
	$(CC) $(CFLAGS) \
	$(UNIT_DIR)/test_uart_cmd.c \
	$(APP_SRC)/app_uart.c \
	-o test_uart_cmd
	./test_uart_cmd


# =========================
# New Embedded C++ Logic Tests
# =========================

# Header-only / simple class
test_cpp:
	$(CXX) $(CXXFLAGS) \
	$(TEST_DIR)/test_pump_controller.cpp \
	-o test_pump_controller
	./test_pump_controller


# Real production C++ source + test
test_cpp_full:
	$(CXX) $(CXXFLAGS) \
	$(APP_SRC)/pump_controller.cpp \
	$(TEST_DIR)/test_pump_controller.cpp \
	-o test_pump_controller
	./test_pump_controller


# =========================
# Convenience Target
# =========================

all_tests: run cmd matrix test_uart test_cpp


# =========================
# Clean
# =========================

clean:
	rm -f \
	test_app \
	test_cmd \
	test_state_matrix \
	thread_demo \
	test_uart_cmd \
	test_pump_controller