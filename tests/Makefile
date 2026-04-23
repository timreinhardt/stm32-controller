CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../App/Inc

run:
	$(CC) $(CFLAGS) ../App/Src/app.c unit/test_app.c -o test_app
	./test_app

cmd:
	$(CC) $(CFLAGS) ../App/Src/app.c ../App/Src/app_cmd.c unit/test_cmd.c -o test_cmd
	./test_cmd

thread:
	$(CC) $(CFLAGS) concurrency/thread_demo.c -o thread_demo
	./thread_demo

clean:
	rm -f test_app test_cmd thread_demo