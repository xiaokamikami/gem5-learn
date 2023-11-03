CC=riscv64-linux-gnu-gcc
CFLAGS=-O3 -static

all: array

array: array.c
	$(CC) $(CFLAGS) -o ../bin/riscv/linux/array array.c

clean:
	rm -f array
