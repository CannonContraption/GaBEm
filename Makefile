CC = gcc
CFLAGS = -Wall -Werror -O2 -g -Iinclude
CLIBFLAGS = -fPIC

build/gabem: src/main.c src/cpu.h src/cpu.c src/regsmem.h src/regsmem.c build
	gcc src/main.c -o build/gabem

build/test: src/test.c src/cpu.h src/cpu.c src/regsmem.h src/regsmem.c build
	gcc src/test.c -o build/test

test: build/test
	./build/test

build:
	mkdir -p build

clean:
	rm -rv build

