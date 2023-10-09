CC = gcc
CFLAGS = -Wall -Werror -O2 -g -Iinclude
CLIBFLAGS = -fPIC

build/gabem: src/main.c src/cpu.h src/regsmem.h src/regsmem.c build
	gcc src/main.c -o build/gabem

build:
	mkdir -p build

clean:
	rm -rv build

