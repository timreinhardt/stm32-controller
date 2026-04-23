CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../Core/Inc

SRC = ../Core/Src/app.c test_app.c
OUT = test_app

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)