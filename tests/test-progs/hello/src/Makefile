CC=riscv64-linux-gnu-gcc
CFLAGS=-O3 -static

all: hello

hello: hello.c
	$(CC) $(CFLAGS) -o ../bin/riscv/linux/hello hello.c

clean:
	rm -f hello
