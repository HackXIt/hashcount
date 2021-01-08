CC=gcc
INC=-iquote/home/rini-debian/git-stash/HWSE/project_hashcount/inc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g
BUILD=./build/
# VPATH:=src:build
vpath %.o ./build
vpath %.c ./src
vpath %.h ./inc

all: hashcount

$(BUILD)%.o: %.c %.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# hash-utils.o: hash-utils.c hash-utils.h
# 	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

# list-utils.o: list-utils.c list-utils.h
# 	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

# file-utils.o: file-utils.c file-utils.h
# 	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

# hashcount.o: hashcount.c
# 	$(CC) $(CFLAGS) -c $< -o $(BUILD)$@

hashcount: hashcount.o hash-utils.o list-utils.o file-utils.o
	$(CC) $(CFLAGS) $^ -o $@

# I know I shouldn't use something else with $@
# But this shit just doesn't work without it, so yea...
temp: $(BUILD)hash-utils.o $(BUILD)list-utils.o $(BUILD)hashcount.o
	$(CC) $(CFLAGS) $^ -o $(BUILD)$@

clean:
	rm $(BUILD)*.o $(BUILD)hashcount
