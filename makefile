CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g
BUILD=./build/
SRC=./src/

all: hashcount

hash-utils: $(SRC)hash-utils.h $(SRC)hash-utils.c
	$(CC) $(CFLAGS) -c $^ -o $(BUILD)$@.o

list-utils: $(SRC)list-utils.h $(SRC)list-utils.c
	$(CC) $(CFLAGS) -c $^ -o $(BUILD)$@.o

file-utils: $(SRC)file-utils.h $(SRC)file-utils.c
	$(CC) $(CFLAGS) -c $^ -o $(BUILD)$@.o

hashcount: $(BUILD)hash-utils.o $(BUILD)list-utils.o $(BUILD)file-utils.o $(SRC)hashcount.c
	$(CC) $(CFLAGS) $^ -o $(BUILD)$@

clean:
	rm $(BUILD)*.o $(BUILD)hashcount
