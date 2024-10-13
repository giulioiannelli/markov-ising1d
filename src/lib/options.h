// options.h

#ifndef OPTIONS_H
#define OPTIONS_H

#include <getopt.h>
#include "utils.h"

#define DEFAULT_K 1
#define DEFAULT_OUTPUT_FNAME "ising1d"

// Structure to hold parsed command-line options
typedef struct {
    bool verbose;          // Flag for verbose mode
    uint32_t N;     // Input file name
    double T;
    uint64_t conf_num;
    char *output_file;    // Output file name
    int rand_seed;        // Flag to set seed randomly
} Options;

// Function to parse command-line arguments
// Returns 0 on success, non-zero on failure
int parse_arguments(int argc, char *argv[], Options *opts);
void print_usage(const char *prog_name);

#endif // OPTIONS_H
