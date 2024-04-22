CC = gcc 
CFLAGS = -g -W -Wall -std=c99 -pedantic -O2
CLIBS = -lm -lMLV

CODEC = huffman_tree.o node.o alphabet.o compression.o decompression.o data.o
UTILS = utils.o file.o folder.o bit.o
DEBUG = debug.o

COMPONENTS = gui.o button.o image.o text.o window.o color.o rectangle.o cross.o topbar.o padding.o
GUI_UTILS = position.o dimension.o
PAGES = home.o
MANAGER = mouse_manager.o layout_manager.o

all: build simple-clean

clean-example:
	rm -rf ./example/*/*.bin ./example/*/decompressed_*

build: main.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) $(PAGES)
	$(CC) main.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) $(PAGES) -o main $(CLIBS)

install:
	./setup.sh

# ----------- #
# Main file 
# ----------- #
main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c

# ---------------------------------------------------- #
#                        HUFFMAN 					   #
# ---------------------------------------------------- #

# ----------- #
# CODEC 
# ----------- #
huffman_tree.o: ./src/huffman/codec/coding/tree/huffman_tree.c
	$(CC) $(CFLAGS) -c ./src/huffman/codec/coding/tree/huffman_tree.c

node.o: ./src/huffman/codec/coding/tree/node.c
	$(CC) $(CFLAGS) -c ./src/huffman/codec/coding/tree/node.c

alphabet.o: ./src/huffman/codec/coding/alphabet/alphabet.c
	$(CC) $(CFLAGS) -c ./src/huffman/codec/coding/alphabet/alphabet.c

compression.o: ./src/huffman/codec/compression/compression.c
	$(CC) $(CFLAGS) -c ./src/huffman/codec/compression/compression.c

data.o: ./src/huffman/codec/compression/data.c
	$(CC) $(CFLAGS) -c ./src/huffman/codec/compression/data.c

decompression.o: ./src/huffman/codec/decompression/decompression.c
	$(CC) $(CFLAGS) -c ./src/huffman/codec/decompression/decompression.c



# ----------- #
# DEBUG
# ----------- #
debug.o: ./src/debug/debug.c
	$(CC) $(CFLAGS) -c ./src/debug/debug.c


# ----------- #
# UTILS
# ----------- #
utils.o: ./src/huffman/utils/utils.c
	$(CC) $(CFLAGS) -c ./src/huffman/utils/utils.c

file.o: ./src/huffman/utils/file/file.c
	$(CC) $(CFLAGS) -c ./src/huffman/utils/file/file.c

folder.o: ./src/huffman/utils/folder/folder.c
	$(CC) $(CFLAGS) -c ./src/huffman/utils/folder/folder.c

bit.o: ./src/huffman/utils/byte/bit.c
	$(CC) $(CFLAGS) -c ./src/huffman/utils/byte/bit.c



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

rectangle.o: ./src/gui/components/shape/rectangle/rectangle.c
	$(CC) $(CFLAGS) -c ./src/gui/components/shape/rectangle/rectangle.c

cross.o: ./src/gui/components/shape/cross/cross.c
	$(CC) $(CFLAGS) -c ./src/gui/components/shape/cross/cross.c

text.o: ./src/gui/components/text/text.c
	$(CC) $(CFLAGS) -c ./src/gui/components/text/text.c

window.o: ./src/gui/components/window/window.c
	$(CC) $(CFLAGS) -c ./src/gui/components/window/window.c

color.o: ./src/gui/components/color/color.c
	$(CC) $(CFLAGS) -c ./src/gui/components/color/color.c

topbar.o: ./src/gui/components/topbar/topbar.c
	$(CC) $(CFLAGS) -c ./src/gui/components/topbar/topbar.c

padding.o: ./src/gui/components/padding/padding.c
	$(CC) $(CFLAGS) -c ./src/gui/components/padding/padding.c

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

layout_manager.o: ./src/gui/manager/layout_manager/layout_manager.c
	$(CC) $(CFLAGS) -c ./src/gui/manager/layout_manager/layout_manager.c

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