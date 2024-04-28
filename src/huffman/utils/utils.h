#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include "../../constants.h"
#include "./file/file.h"

/**
 * @brief This function convert a code into a string
 *
 * @param code - the code to convert
 * @param size - the size of the code
 * @return char* - the string
 */
char *convert_code_into_string(int *code, int size);

/**
 * @brief This function convert a string into a code
 *
 * @param str - the string to convert
 * @param size - the size of the string
 * @return int* - the code
 */
int *convert_string_into_code(char *str, int size);

/**
 * @brief This function compare two arrays
 *
 * @param arr1 - the first array
 * @param arr2 - the second array
 * @param processed_length - the length of the processed part
 * @param size - the size of the arrays
 * @return int - 1 if the arrays are equal, 0 otherwise
 */
int are_arrays_equal(int *arr1, int *arr2, int processed_length, int size);

/**
 * @brief This function initialize the frequencies of each character in a file
 *
 * @param char_frequencies - the array to initialize
 */
void initialize_char_frequencies(int *char_frequencies);

/**
 * @brief This function count the frequencies of each character in a file
 *
 * @param file - the file to read
 * @param char_frequencies - the array to store the frequencies
 */
void count_char_frequencies(FILE *file, int *char_frequencies);

/**
 * @brief This function get the number of unique characters in a file
 *
 * @param char_frequencies - the array of frequencies
 * @return int - the number of unique characters
 */
int get_number_of_unique_chars(int *char_frequencies);

/**
 * @brief This function get the ASCII value of the unique characters in a file
 *
 * @param char_frequencies - the array of frequencies
 * @return int - the ASCII value
 */
int get_ascii_of_unique_char(int *char_frequencies);

/**
 * @brief This function concatenate a prefix to a string
 *
 * @param str - the string
 * @param prefix - the prefix
 */
void str_cat_prefix(char *str, const char *prefix);

/**
 * @brief This function split a string into parts
 *
 * @param str - the string to split
 * @param parts - the array of parts
 * @param delimiter - the delimiter
 * @return int - the number of parts
 */
int split_string(char *str, char **parts, const char *delimiter);

/**
 * @brief This function get the number of digits of a number
 *
 * @param number - the number
 * @return int - the number of digits
 */
int max(int a, int b);

/**
 * @brief This function get the minimum of two numbers
 *
 * @param a - the first number
 * @param b - the second number
 * @return int - the minimum
 */
int min(int a, int b);

/**
 * @brief This function delete a file or a directory
 *
 * @param path - the path of the file or directory
 * @return int - 1 if the deletion is successful, 0 otherwise
 */
int delete_file_or_directory(const char *path);

/**
 * @brief Compute the compression type
 *
 * @param path - the path of the files
 * @param num_files - the number of files
 * @return Type - the compression type
 */
Type compute_compression_type(char **path, int num_files);

#endif