.PHONY: run

run: gameboy
	./gameboy

gameboy:
	gcc -Wall -Wextra -g3 -o gameboy main.c registers.c

