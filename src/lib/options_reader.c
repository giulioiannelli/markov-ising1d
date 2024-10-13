#include "utils.h"
#include "options_reader.h"

// Function to print usage/help message
void print_usage(const char *prog_name) {
    printf("Usage: %s [OPTIONS] binary_file mode N [output_file]\n", prog_name);
    printf("\nPositional Arguments:\n");
    printf("  binary_file\tPath to the binary file containing configurations. (mandatory)\n");
    printf("  mode\t\tOperation mode ('file' to write to a text file, 'stdout' to print to stdout). (mandatory)\n");
    printf("  N\t\tLength of each configuration (number of +1/-1 entries). (mandatory)\n");
    printf("\nOptions:\n");
    printf("  -o, --output\tPath to the output text file.\n");
    printf("  -h, --help\t\tDisplay this help message.\n");
    printf("  -v, --verbose\t\tEnable verbose mode.\n");
    printf("\nExamples:\n");
    printf("  %s -v data.bin file 100 output.txt\n", prog_name);
    printf("  %s --verbose  data.bin stdout 100\n", prog_name);
}

// Function to parse and validate command-line arguments
int parse_arguments(int argc, char *argv[], Options *opts) {
    int opt;
    int option_index = 0;

    // Initialize options with default values
    opts->verbose = false;
    opts->output_file = DEFAULT_OUTPUT_FILE;
    opts->binary_file = NULL;
    opts->mode = NULL;
    opts->N = 0;

    // Define long options
    static struct option long_options[] = {
        {"verbose",   no_argument,       0, 'v'},
        {"conf_num",  required_argument, 0, 'k'},
        {"output",    required_argument, 0, 'o'},
        {"help",      no_argument,       0, 'h'},
        {"rand_seed", no_argument,       0, 'r'},
        {0,           0,                 0,  0 }
    };

    // Parse options using getopt_long
    while ((opt = getopt_long(argc, argv, "vk:o:hr", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                opts->verbose = true;
                break;
            case 'o':
                opts->output_file = optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                print_usage(argv[0]);
                return 1; // Indicate failure
        }
    }

    // After option parsing, expect exactly three or four positional arguments:
    // binary_file, mode, N, [output_file]
    int remaining_args = argc - optind;
    if (remaining_args < 3 || remaining_args > 4) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        print_usage(argv[0]);
        return 1;
    }

    // Assign positional arguments
    opts->binary_file = argv[optind];
    opts->mode = argv[optind + 1];
    opts->N = strtoul_check(argv[optind + 2], 10);

    if (strcmp(opts->mode, "file") && strcmp(opts->mode, "stdout")) {
        fprintf(stderr, "Error: Invalid mode '%s'. Must be 'file' or 'stdout'.\n", opts->mode);
        print_usage(argv[0]);
        return 1;
    }

    return 0; // Indicate success
}
