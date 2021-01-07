CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g
BUILD=build/
VPATH=src:build

all: hashcount

temp: hash-utils.o list-utils.o
	$(CC) $(CFLAGS) $^ -o $(BUILD)$@

hash-utils.o: hash-utils.c hash-utils.h
	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

list-utils.o: list-utils.c list-utils.h
	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

file-utils.o: file-utils.c file-utils.h
	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

hashcount.o: hashcount.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

hashcount: hashcount.o hash-utils.o list-utils.o file-utils.o
	$(CC) $(CFLAGS) $^ -o $(BUILD)$@

clean:
	rm $(BUILD)*.o $(BUILD)hashcount
