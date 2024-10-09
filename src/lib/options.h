// options.h

#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>
#include "utils.h"

// Structure to hold parsed command-line options
typedef struct {
    int verbose;          // Flag for verbose mode
    uint64_t conf_num;
    char *output_file;    // Output file name
    uint32_t N;     // Input file name
    double T;
} Options;

// Function to parse command-line arguments
// Returns 0 on success, non-zero on failure
int parse_arguments(int argc, char *argv[], Options *opts);
// Function to print usage/help message
void print_usage(const char *prog_name);

#endif // OPTIONS_H
