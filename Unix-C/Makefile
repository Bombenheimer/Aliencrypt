CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -g
LDFLAGS=-lsodium -lexif

all: alien

alien: alien.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

alien.o: alien.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f alien alien.o
