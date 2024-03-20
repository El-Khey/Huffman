CC = gcc 
CFLAGS = -g -W -Wall -std=c89 -pedantic -O2
CLIBS = -lm -lMLV


all: build simple-clean

build: main.o binary_tree.o
	$(CC) main.o binary_tree.o -o main $(CLIBS)

# ----------- #
# Main file 
# ----------- #

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

binary_tree.o: ./binary_tree/binary_tree.c
	$(CC) $(CFLAGS) -c ./binary_tree/binary_tree.c


# simple-clean removes all the .o files
simple-clean:
	rm -rf *.o

# Clean removes all the .o files and the executable
clean: simple-clean
	rm -rf main