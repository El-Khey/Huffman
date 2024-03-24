CC = gcc 
CFLAGS = -g -W -Wall -std=c89 -pedantic -O2
CLIBS = -lm -lMLV

TREE = huffman_tree.o node.o alphabet.o
UTILS = utils.o file.o
COMPRESSION = compression.o decompression.o

all: build simple-clean

build: main.o $(TREE) $(UTILS) $(COMPRESSION)
	$(CC) main.o $(TREE) $(UTILS) $(COMPRESSION) -o main $(CLIBS)

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

alphabet.o: ./src/tree/alphabet.c
	$(CC) $(CFLAGS) -c ./src/tree/alphabet.c


# ----------- #
# UTILS
# ----------- #

utils.o: ./src/utils/utils.c
	$(CC) $(CFLAGS) -c ./src/utils/utils.c

file.o: ./src/utils/file.c
	$(CC) $(CFLAGS) -c ./src/utils/file.c

compression.o: ./src/compression/compression.c
	$(CC) $(CFLAGS) -c ./src/compression/compression.c

decompression.o: ./src/decompression/decompression.c
	$(CC) $(CFLAGS) -c ./src/decompression/decompression.c

# simple-clean removes all the .o files
simple-clean:
	rm -rf *.o

# Clean removes all the .o files and the executable
clean: simple-clean
	rm -rf main