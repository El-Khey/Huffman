CC = gcc 
CFLAGS = -g -W -Wall -std=c89 -pedantic -O2
CLIBS = -lm -lMLV

TREE = huffman_tree.o node.o
UTILS = utils.o file.o

all: build simple-clean

build: main.o $(TREE) $(UTILS)
	$(CC) main.o $(TREE) $(UTILS) -o main $(CLIBS)

# ----------- #
# Main file 
# ----------- #

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c


# ----------- #
# TREE 
# ----------- #

huffman_tree.o: ./src/tree/huffman_tree.c
	$(CC) $(CFLAGS) -c ./src/tree/huffman_tree.c

node.o: ./src/tree/node.c
	$(CC) $(CFLAGS) -c ./src/tree/node.c


# ----------- #
# UTILS
# ----------- #

utils.o: ./src/utils/utils.c
	$(CC) $(CFLAGS) -c ./src/utils/utils.c

file.o: ./src/utils/file.c
	$(CC) $(CFLAGS) -c ./src/utils/file.c

# simple-clean removes all the .o files
simple-clean:
	rm -rf *.o

# Clean removes all the .o files and the executable
clean: simple-clean
	rm -rf main