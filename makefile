# Please don't grade my makefile
# It was my FIRST ever time using make and creating a makefile.
# Keeping that in mind, I think it turned out pretty well.. because it works.
# But I know it's flawed, at least according to:
# http://make.mad-scientist.net/papers/rules-of-makefiles/
# and this http://make.mad-scientist.net/papers/how-not-to-use-vpath/

# MAKE learning resources ---
# Compiling C programs with Multiple Files
# https://www.youtube.com/watch?v=2YfM-HxQd_8
# Learn make in 60 seconds.
# https://www.youtube.com/watch?v=a8mPKBxQ9No
# How to Create a Simple Makefile - Introduction to Makefiles
# https://www.youtube.com/watch?v=_r7i5X0rXJk
# automatic variables for smaller and easier to maintain makefiles
# https://www.youtube.com/watch?v=G5dNorAoeCM

CC=gcc
INC=-iquote/home/rini-debian/git-stash/HWSE/project_hashcount/inc
CFLAGS=-std=c99 -Wall -Wextra -pedantic -g
BUILD=./build/
# VPATH:=src:build
vpath %.o ./build
vpath %.c ./src
vpath %.h ./inc

all: hashcount

# This is required because hashcount doesn't have a header-file
# Thus the automatic variable doesn't work.
$(BUILD)hashcount.o: hashcount.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

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

# hashcount: hashcount.o hash-utils.o list-utils.

# I know I shouldn't use something else with $@
# But this shit just doesn't work without it, so yea...
temp: $(BUILD)hash-utils.o $(BUILD)list-utils.o $(BUILD)file-utils.o $(BUILD)hashcount.o
	$(CC) $(CFLAGS) $^ -o $(BUILD)$@

clean:
	rm $(BUILD)*.o $(BUILD)hashcount
