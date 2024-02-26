all: build run

build: final.c
	gcc final.c -o final -lintelfpgaup -std=c99

run: final
	./final

clean:
	rm -f final

.PHONY: all build run clean
