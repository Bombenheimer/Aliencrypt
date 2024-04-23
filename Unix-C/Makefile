CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -march=native -g
LDFLAGS=-lsodium -lexif
MAN_DIR=/usr/local/share/man/man8
BIN_DIR=/usr/local/bin

all: alien

alien: alien.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

alien.o: alien.c
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	install -d $(MAN_DIR)
	install -m 644 man/alien.8 $(MAN_DIR)
	install -m 711 alien $(BIN_DIR)
	chown root $(BIN_DIR)/alien

clean:
	rm -f alien.o
