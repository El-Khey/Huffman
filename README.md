# Huffman Compression and Decompression

This is a simple command-line tool for compressing and decompressing files using Huffman coding.

## Installation

Clone the repository and launch 

```bash
make install
```

to install the MLV library.

Then, build the project with

```bash
make
```

## Usage

The tool can be used with the following command-line options:

- `-c <archive_name> <input_files/directories>`: Compress files or directories. The compressed output will be stored in `archive_name`.
- `-d <input_file> [output_directory]`: Decompress a file. The decompressed output will be stored in `output_directory` if provided, otherwise in the current directory.
- `-h`: Display help.

Example usages:

```bash
# Compress a file
./huffman -c archive.huff input.txt

# Compress a directory
./huffman -c archive.huff ./input_directory

# Decompress a file to the current directory
./huffman -d archive.huff

# Decompress a file to a specific directory
./huffman -d archive.huff ./output_directory

# compress a list of files or directories
./huffman -c archive.huff input1.txt input2.txt ./folder1 ./folder2
```