#include "options.h"
// Function to print usage/help message
void print_usage(const char *prog_name) {
    printf("Usage: %s [OPTIONS] N T\n", prog_name);
    printf("Positional Arguments:\n");
    printf("\tN\t\t\tParameter N. (mandatory)\n");
    printf("\tT\t\t\tParameter T. (mandatory)\n");
    printf("\nOptions:\n");
    printf("\t-h, --help\t\t\t\tDisplay this help message.\n");
    printf("\t-v, --verbose\t\t\t\tEnable verbose mode.\n");
    printf("\t-k, --conf_num\t\tK\t\tNumber of configurations to save. [default: %d]\n", DEFAULT_K);
    printf("\t-o, --output\t\tFILE\t\tSpecify output file. [default: %s]\n", DEFAULT_OUTPUT_FILE);
    printf("\t-r, --rand_seed\t\tSEED\t\tSet the seed randomly.\n");
}

// Function to parse command-line arguments
int parse_arguments(int argc, char *argv[], Options *opts) {
    int opt;
    int option_index = 0;
    
    // Initialize options with default values
    opts->verbose = 0;
    opts->rand_seed = 0;
    opts->conf_num = DEFAULT_K;
    opts->output_file = DEFAULT_OUTPUT_FILE; // Default output file

    // Define long options
    static struct option long_options[] = {
        {"verbose",   no_argument,       0, 'v'},
        {"conf_num",  required_argument, 0, 'k'},
        {"output",    required_argument, 0, 'o'},
        {"help",      no_argument,       0, 'h'},
        {"rand_seed", no_argument, 0, 'r'},
        {0,           0,                 0,  0 }
    };

    // Parse options using getopt_long
    while ((opt = getopt_long(argc, argv, "vk:o:hr:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'v':
                opts->verbose = 1;
                break;
            case 'o':
                opts->output_file = optarg;
                break;
            case 'k':
                opts->conf_num = strtoull_check(optarg, 10);
                break;
            case 'r':
                opts->rand_seed = 1;
                break;
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
        fprintf(stderr, ERR_MESSAGE_ARGS, remaining_args);
        print_usage(argv[0]);
        return 1;
    }
    opts->N = strtoul_check(argv[optind], 10);
    opts->T = strtodb_check(argv[optind + 1]);
    return 0; // Indicate success
}
