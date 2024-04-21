CC = gcc 
CFLAGS = -g -W -Wall -std=c99 -pedantic -O2
CLIBS = -lm -lMLV

TREE = huffman_tree.o node.o alphabet.o
UTILS = utils.o file.o folder.o 
COMPRESSION = compression.o decompression.o data.o
BYTE = bit.o
DEBUG = debug.o

COMPONENTS = gui.o button.o image.o shape.o text.o window.o color.o
GUI_UTILS = position.o dimension.o
PAGES = home.o
MANAGER = mouse_manager.o

all: build simple-clean

clean-example:
	rm -rf ./example/*/*.bin ./example/*/decompressed_*

build: main.o $(TREE) $(UTILS) $(BYTE) $(COMPRESSION) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) $(PAGES)
	$(CC) main.o $(TREE) $(UTILS) $(BYTE) $(COMPRESSION) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) $(PAGES) -o main $(CLIBS)

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



# ---------------------------------------------------- #
#                        GUI 						   #
# ---------------------------------------------------- #

# ----------- #
# GUI
# ----------- #
gui.o: ./src/gui/gui.c
	$(CC) $(CFLAGS) -c ./src/gui/gui.c

button.o: ./src/gui/components/button/button.c
	$(CC) $(CFLAGS) -c ./src/gui/components/button/button.c

image.o: ./src/gui/components/image/image.c
	$(CC) $(CFLAGS) -c ./src/gui/components/image/image.c

shape.o: ./src/gui/components/shape/shape.c
	$(CC) $(CFLAGS) -c ./src/gui/components/shape/shape.c

text.o: ./src/gui/components/text/text.c
	$(CC) $(CFLAGS) -c ./src/gui/components/text/text.c

window.o: ./src/gui/components/window/window.c
	$(CC) $(CFLAGS) -c ./src/gui/components/window/window.c

color.o: ./src/gui/components/color/color.c
	$(CC) $(CFLAGS) -c ./src/gui/components/color/color.c

# ----------- #
# GUI UTILS
# ----------- #
position.o: ./src/gui/utils/position/position.c
	$(CC) $(CFLAGS) -c ./src/gui/utils/position/position.c

dimension.o: ./src/gui/utils/dimension/dimension.c
	$(CC) $(CFLAGS) -c ./src/gui/utils/dimension/dimension.c


# ----------- #
# MANAGER
# ----------- #
mouse_manager.o: ./src/gui/manager/mouse_manager/mouse_manager.c
	$(CC) $(CFLAGS) -c ./src/gui/manager/mouse_manager/mouse_manager.c

# ----------- #
# PAGES
# ----------- #
home.o: ./src/gui/pages/home/home.c
	$(CC) $(CFLAGS) -c ./src/gui/pages/home/home.c

	

# simple-clean removes all the .o files
simple-clean:
	rm -rf *.o

# Clean removes all the .o files and the executable
clean: simple-clean
	rm -rf main