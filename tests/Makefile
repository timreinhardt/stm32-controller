CC = gcc
CFLAGS = -DUNIT_TEST -Wall -Wextra -std=c11 -I../App/Inc
PTHREAD_FLAGS = -pthread

run:
	$(CC) $(CFLAGS) ../App/Src/app.c ../App/Src/app_state.c unit/test_app.c -o test_app
	./test_app

cmd:
	$(CC) $(CFLAGS) ../App/Src/app.c ../App/Src/app_state.c ../App/Src/app_cmd.c unit/test_cmd.c -o test_cmd
	./test_cmd

matrix:
	$(CC) $(CFLAGS) ../App/Src/app.c ../App/Src/app_state.c unit/test_state_matrix.c -o test_state_matrix
	./test_state_matrix

thread:
	$(CC) $(CFLAGS) concurrency/thread_demo.c -o thread_demo $(PTHREAD_FLAGS)
	./thread_demo

test_uart:
	$(CC) $(CFLAGS) unit/test_uart_cmd.c ../App/Src/app_uart.c -o test_uart_cmd
	./test_uart_cmd

clean:
	rm -f test_app test_cmd test_state_matrix thread_demo test_uart_cmd