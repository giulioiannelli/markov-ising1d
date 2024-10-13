// options_reader.h

#ifndef OPTIONS_READER_H
#define OPTIONS_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
// Default values
#define DEFAULT_OUTPUT_FILE "output.txt"

// Structure to hold parsed options
typedef struct {
    bool verbose;            // Enable verbose mode
    char *binary_file;       // Binary file path
    char *mode;              // Operation mode: "file" or "stdout"
    char *output_file;       // Output file path
    uint32_t N;              // Length of each configuration
} Options;

// Function to print usage/help message
void print_usage(const char *prog_name);
// Function to parse and validate command-line arguments
// Returns 0 on success, non-zero on failure
int parse_arguments(int argc, char *argv[], Options *opts);

#endif // OPTIONS_READER_H