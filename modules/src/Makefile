CC=gcc
CLIBS=-lintelfpgaup
CFLAGS=-Wall -std=c99

SRC=main.c
OUT=main

all: build run

build: $(SRC)
	gcc $(SRC) -o $(OUT) $(CLIBS) $(CFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

.PHONY: all build run clean
