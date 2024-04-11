CC = gcc 
CFLAGS = -g -W -Wall -std=c99 -pedantic -O2
CLIBS = -lm -lMLV

TREE = huffman_tree.o node.o alphabet.o
UTILS = utils.o file.o folder.o
COMPRESSION = compression.o decompression.o data.o
BYTE = bit.o
DEBUG = debug.o

all: build simple-clean

clean-example:
	rm -rf ./example/*/*.bin ./example/*/decompressed_*

build: main.o $(TREE) $(UTILS) $(BYTE) $(COMPRESSION) $(DEBUG)
	$(CC) main.o $(TREE) $(UTILS) $(BYTE) $(COMPRESSION) $(DEBUG) -o main $(CLIBS)

install:
	./setup.sh

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
# BYTE
# ----------- #
bit.o: ./src/byte/bit.c
	$(CC) $(CFLAGS) -c ./src/byte/bit.c


# ----------- #
# DEBUG
# ----------- #
debug.o: ./src/debug/debug.c
	$(CC) $(CFLAGS) -c ./src/debug/debug.c


# ----------- #
# UTILS
# ----------- #
utils.o: ./src/utils/utils.c
	$(CC) $(CFLAGS) -c ./src/utils/utils.c

file.o: ./src/utils/file.c
	$(CC) $(CFLAGS) -c ./src/utils/file.c

compression.o: ./src/compression/compression.c
	$(CC) $(CFLAGS) -c ./src/compression/compression.c

data.o: ./src/compression/data.c
	$(CC) $(CFLAGS) -c ./src/compression/data.c

decompression.o: ./src/decompression/decompression.c
	$(CC) $(CFLAGS) -c ./src/decompression/decompression.c

folder.o: ./src/utils/folder.c
	$(CC) $(CFLAGS) -c ./src/utils/folder.c

# simple-clean removes all the .o files
simple-clean:
	rm -rf *.o

# Clean removes all the .o files and the executable
clean: simple-clean
	rm -rf main