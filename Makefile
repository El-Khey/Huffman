# ==================================================== #
#          C O M P I L A T I O N   S E T U P           #
# ==================================================== #
#            defines the compiler and flags            #
# ---------------------------------------------------- #


CC = gcc 
CFLAGS = -g -W -Wall -std=c99 -pedantic -O2
CLIBS = -lm -lMLV -lSDL


# ==================================================== #
#         T A R G E T S   D E C L A R A T I O N        #
# ==================================================== #
# 		   defines the targets of the makefile         #
# ---------------------------------------------------- #

CODEC = huffman_tree.o node.o alphabet.o compression.o decompression.o data.o
UTILS = utils.o file.o folder.o bit.o
DEBUG = debug.o

GUI_UTILS = position.o dimension.o
MANAGER = mouse_manager.o layout_manager.o explorer.o gui_manager.o gui_event_manager.o
COMPONENTS = gui.o button.o image.o text.o window.o color.o rectangle.o cross.o padding.o topbar.o \
			 navbar.o table.o checkbox.o footer.o

all: build simple-clean

build: main.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER)
	$(CC) main.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) -o main $(CLIBS)

install:
	./setup.sh

# ==================================================== #
#            	 H U F F  V E R S I O N S              #
# ==================================================== #
# 		   defines the targets of the versions         #
# ---------------------------------------------------- #

MAIN_VERSIONS = main_v1.o main_v2.o main_v3.o main_v4.o main_v5.o

build-v1: main_v1.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER)
	$(CC) main_v1.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) -o main_v1 $(CLIBS)

build-v2: main_v2.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER)
	$(CC) main_v2.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) -o main_v2 $(CLIBS)

build-v3: main_v3.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER)
	$(CC) main_v3.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) -o main_v3 $(CLIBS)

build-v4: main_v4.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER)
	$(CC) main_v4.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) -o main_v4 $(CLIBS)

build-v5: main_v5.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER)
	$(CC) main_v5.o $(CODEC) $(UTILS) $(DEBUG) $(COMPONENTS) $(GUI_UTILS) $(MANAGER) -o main_v5 $(CLIBS)

main_v1.o: ./src/version/main_v1.c
	$(CC) $(CFLAGS) -c ./src/version/main_v1.c

main_v2.o: ./src/version/main_v2.c
	$(CC) $(CFLAGS) -c ./src/version/main_v2.c

main_v3.o: ./src/version/main_v3.c
	$(CC) $(CFLAGS) -c ./src/version/main_v3.c

main_v4.o: ./src/version/main_v4.c
	$(CC) $(CFLAGS) -c ./src/version/main_v4.c

main_v5.o: ./src/version/main_v5.c
	$(CC) $(CFLAGS) -c ./src/version/main_v5.c

v1: build-v1 simple-clean
v2: build-v2 simple-clean
v3: build-v3 simple-clean
v4: build-v4 simple-clean
v5: build-v5 simple-clean
v-all: build-v1 build-v2 build-v3 build-v4 build-v5 simple-clean


# ---------------------------------------------------- #
#                        HUFFMAN 					   #
# ---------------------------------------------------- #

main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c

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

navbar.o: ./src/gui/components/navbar/navbar.c
	$(CC) $(CFLAGS) -c ./src/gui/components/navbar/navbar.c

padding.o: ./src/gui/components/padding/padding.c
	$(CC) $(CFLAGS) -c ./src/gui/components/padding/padding.c

table.o: ./src/gui/components/table/table.c
	$(CC) $(CFLAGS) -c ./src/gui/components/table/table.c

checkbox.o: ./src/gui/components/checkbox/checkbox.c
	$(CC) $(CFLAGS) -c ./src/gui/components/checkbox/checkbox.c

footer.o: ./src/gui/components/footer/footer.c
	$(CC) $(CFLAGS) -c ./src/gui/components/footer/footer.c

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

explorer.o: ./src/gui/manager/explorer/explorer.c
	$(CC) $(CFLAGS) -c ./src/gui/manager/explorer/explorer.c

gui_manager.o: ./src/gui/manager/gui_manager/gui_manager.c
	$(CC) $(CFLAGS) -c ./src/gui/manager/gui_manager/gui_manager.c

gui_event_manager.o: ./src/gui/manager/gui_manager/gui_event_manager.c
	$(CC) $(CFLAGS) -c ./src/gui/manager/gui_manager/gui_event_manager.c


# ==================================================== #
#          	 T E S T S  G E N E R A T I O N            #
# ==================================================== #
# 		   generates the test files for the study      #
# ---------------------------------------------------- #

generate-test:
	./study/generator/generator.sh

create-compressed-dirs:
	mkdir -p ./study/test/compressed/linear/ ./study/test/compressed/uniform/ \
	./study/test/compressed/normal/ ./study/test/compressed/zipf/ \
	./study/test/compressed/random/

run-linear:
	./main -c ./study/test/compressed/linear/linear_1000_94.bin ./study/test/raw/linear/linear_1000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_5000_94.bin ./study/test/raw/linear/linear_5000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_10000_94.bin ./study/test/raw/linear/linear_10000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000_94.bin ./study/test/raw/linear/linear_50000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_100000_94.bin ./study/test/raw/linear/linear_100000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_500000_94.bin ./study/test/raw/linear/linear_500000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_1000000_94.bin ./study/test/raw/linear/linear_1000000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_5000000_94.bin ./study/test/raw/linear/linear_5000000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_10000000_94.bin ./study/test/raw/linear/linear_10000000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_94.bin ./study/test/raw/linear/linear_50000000_94.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_2.bin ./study/test/raw/linear/linear_50000000_2.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_4.bin ./study/test/raw/linear/linear_50000000_4.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_8.bin ./study/test/raw/linear/linear_50000000_8.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_16.bin ./study/test/raw/linear/linear_50000000_16.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_32.bin ./study/test/raw/linear/linear_50000000_32.txt &&\
	./main -c ./study/test/compressed/linear/linear_50000000_64.bin ./study/test/raw/linear/linear_50000000_64.txt

run-uniform:
	./main -c ./study/test/compressed/uniform/uniform_1000_94.bin ./study/test/raw/uniform/uniform_1000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_5000_94.bin ./study/test/raw/uniform/uniform_5000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_10000_94.bin ./study/test/raw/uniform/uniform_10000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000_94.bin ./study/test/raw/uniform/uniform_50000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_100000_94.bin ./study/test/raw/uniform/uniform_100000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_500000_94.bin ./study/test/raw/uniform/uniform_500000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_1000000_94.bin ./study/test/raw/uniform/uniform_1000000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_5000000_94.bin ./study/test/raw/uniform/uniform_5000000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_10000000_94.bin ./study/test/raw/uniform/uniform_10000000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_94.bin ./study/test/raw/uniform/uniform_50000000_94.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_2.bin ./study/test/raw/uniform/uniform_50000000_2.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_4.bin ./study/test/raw/uniform/uniform_50000000_4.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_8.bin ./study/test/raw/uniform/uniform_50000000_8.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_16.bin ./study/test/raw/uniform/uniform_50000000_16.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_32.bin ./study/test/raw/uniform/uniform_50000000_32.txt &&\
	./main -c ./study/test/compressed/uniform/uniform_50000000_64.bin ./study/test/raw/uniform/uniform_50000000_64.txt

run-normal:
	./main -c ./study/test/compressed/normal/normal_1000_94.bin ./study/test/raw/normal/normal_1000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_5000_94.bin ./study/test/raw/normal/normal_5000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_10000_94.bin ./study/test/raw/normal/normal_10000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000_94.bin ./study/test/raw/normal/normal_50000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_100000_94.bin ./study/test/raw/normal/normal_100000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_500000_94.bin ./study/test/raw/normal/normal_500000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_1000000_94.bin ./study/test/raw/normal/normal_1000000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_5000000_94.bin ./study/test/raw/normal/normal_5000000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_10000000_94.bin ./study/test/raw/normal/normal_10000000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_94.bin ./study/test/raw/normal/normal_50000000_94.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_2.bin ./study/test/raw/normal/normal_50000000_2.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_4.bin ./study/test/raw/normal/normal_50000000_4.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_8.bin ./study/test/raw/normal/normal_50000000_8.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_16.bin ./study/test/raw/normal/normal_50000000_16.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_32.bin ./study/test/raw/normal/normal_50000000_32.txt &&\
	./main -c ./study/test/compressed/normal/normal_50000000_64.bin ./study/test/raw/normal/normal_50000000_64.txt

run-zipf:
	./main -c ./study/test/compressed/zipf/zipf_1000_94.bin ./study/test/raw/zipf/zipf_1000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_5000_94.bin ./study/test/raw/zipf/zipf_5000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_10000_94.bin ./study/test/raw/zipf/zipf_10000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000_94.bin ./study/test/raw/zipf/zipf_50000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_100000_94.bin ./study/test/raw/zipf/zipf_100000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_500000_94.bin ./study/test/raw/zipf/zipf_500000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_1000000_94.bin ./study/test/raw/zipf/zipf_1000000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_5000000_94.bin ./study/test/raw/zipf/zipf_5000000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_10000000_94.bin ./study/test/raw/zipf/zipf_10000000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_94.bin ./study/test/raw/zipf/zipf_50000000_94.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_2.bin ./study/test/raw/zipf/zipf_50000000_2.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_4.bin ./study/test/raw/zipf/zipf_50000000_4.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_8.bin ./study/test/raw/zipf/zipf_50000000_8.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_16.bin ./study/test/raw/zipf/zipf_50000000_16.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_32.bin ./study/test/raw/zipf/zipf_50000000_32.txt &&\
	./main -c ./study/test/compressed/zipf/zipf_50000000_64.bin ./study/test/raw/zipf/zipf_50000000_64.txt

run-random:
	./main -c ./study/test/compressed/random/random_1000_94.bin ./study/test/raw/random/random_1000_94.txt &&\
	./main -c ./study/test/compressed/random/random_5000_94.bin ./study/test/raw/random/random_5000_94.txt &&\
	./main -c ./study/test/compressed/random/random_10000_94.bin ./study/test/raw/random/random_10000_94.txt &&\
	./main -c ./study/test/compressed/random/random_50000_94.bin ./study/test/raw/random/random_50000_94.txt &&\
	./main -c ./study/test/compressed/random/random_100000_94.bin ./study/test/raw/random/random_100000_94.txt &&\
	./main -c ./study/test/compressed/random/random_500000_94.bin ./study/test/raw/random/random_500000_94.txt &&\
	./main -c ./study/test/compressed/random/random_1000000_94.bin ./study/test/raw/random/random_1000000_94.txt &&\
	./main -c ./study/test/compressed/random/random_5000000_94.bin ./study/test/raw/random/random_5000000_94.txt &&\
	./main -c ./study/test/compressed/random/random_10000000_94.bin ./study/test/raw/random/random_10000000_94.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_94.bin ./study/test/raw/random/random_50000000_94.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_2.bin ./study/test/raw/random/random_50000000_2.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_4.bin ./study/test/raw/random/random_50000000_4.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_8.bin ./study/test/raw/random/random_50000000_8.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_16.bin ./study/test/raw/random/random_50000000_16.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_32.bin ./study/test/raw/random/random_50000000_32.txt &&\
	./main -c ./study/test/compressed/random/random_50000000_64.bin ./study/test/raw/random/random_50000000_64.txt


run-test-linear: all create-compressed-dirs run-linear
run-test-uniform: all create-compressed-dirs run-uniform
run-test-normal: all create-compressed-dirs run-normal
run-test-zipf: all create-compressed-dirs run-zipf
run-test-random: all create-compressed-dirs run-random

run-all-test: all create-compressed-dirs run-linear run-uniform run-normal run-zipf run-random 



# ==================================================== #
#                        C L E A N                     #
# ==================================================== #
# 			clean generates the .o files 			   #			
# ---------------------------------------------------- #

simple-clean:
	rm -rf *.o

clean: simple-clean
	rm -rf mainm main_v? && rm -rf $(MAIN_DIR)/__pycache__ 


# ---------------------------------------------------- #
# 			clean-test removes the test files 		   #
# ---------------------------------------------------- #

clean-test: clean-compressed clean-raw

clean-compressed:
	rm -rf ./study/test/compressed/*

clean-raw:
	rm -rf ./study/test/raw/*/*.txt ./study/test/raw/*/*/*.json ./study/plots/*.png


# ---------------------------------------------------- #