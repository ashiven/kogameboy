.PHONY: run

run: gameboy
	./gameboy

gameboy:
	gcc -Wall -Wextra -g3 -o gameboy src/registers.c src/instructions.c src/cpu.c main.c

