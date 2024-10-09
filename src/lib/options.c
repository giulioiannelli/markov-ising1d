#include "options.h"
// Function to print usage/help message
void print_usage(const char *prog_name) {
    printf("Usage: %s [OPTIONS] N T\n", prog_name);
    printf("Options:\n");
    printf("  -k, --conf_num K        Number of configurations to save. (mandatory)\n");
    printf("  -v, --verbose           Enable verbose mode.\n");
    printf("  -o, --output FILE       Specify output file. [default: output.txt]\n");
    printf("  -h, --help              Display this help message.\n");
    printf("\nPositional Arguments:\n");
    printf("  N                       Parameter N. (mandatory)\n");
    printf("  T                       Parameter T. (mandatory)\n");
}

// Function to parse command-line arguments
int parse_arguments(int argc, char *argv[], Options *opts) {
    int opt;
    int option_index = 0;
    
    // Initialize options with default values
    opts->verbose = 0;
    opts->conf_num = 1;
    opts->output_file = "output.txt"; // Default output file
    opts->N = 0;
    opts->T = 1.0; // Default T value (can be overridden by positional argument)

    // Define long options
    static struct option long_options[] = {
        {"verbose",   no_argument,       0, 'v'},
        {"conf_num",  required_argument, 0, 'k'},
        {"output",    required_argument, 0, 'o'},
        {"help",      no_argument,       0, 'h'},
        {0,           0,                 0,  0 }
    };

    // Parse options using getopt_long
    while ((opt = getopt_long(argc, argv, "vk:o:ho", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                opts->verbose = 1;
                break;
            case 'o':
                opts->output_file = optarg;
                break;
            case 'k': {
                opts->conf_num = strtoull_check(optarg, 10);
            }
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                print_usage(argv[0]);
                return 1; // Indicate failure
        }
    }
    // After option parsing, expect exactly two positional arguments: N and T
    int remaining_args = argc - optind;
    if (remaining_args != 2) {
        fprintf(stderr, "Error: Expected exactly 2 positional arguments (N and T), but got %d.\n", remaining_args);
        print_usage(argv[0]);
        return 1;
    }
    opts->N = strtoul_check(argv[optind], 10);
    opts->T = strtodb_check(argv[optind + 1]);
    return 0; // Indicate success
}
