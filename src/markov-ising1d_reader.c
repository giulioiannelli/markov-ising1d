// markov-ising1d_reader.c - Read binary files containing 1D Ising model configurations
#include "utils.h"
#include "options_reader.h"

int main(int argc, char *argv[]) {
    Options opts;

    // Parse and validate command-line arguments
    if (parse_arguments(argc, argv, &opts) != 0) {
        // parse_arguments already prints the error message
        return EXIT_FAILURE;
    }

    // Validate mode
    if (strcmp(opts.mode, "file") != 0 && strcmp(opts.mode, "stdout") != 0) {
        fprintf(stderr, "Error: Mode must be 'file' or 'stdout'.\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    FILE *f_in;
    __fopen(&f_in, opts.binary_file, "rb");

    // Determine file size
    long file_size = get_file_size(f_in);
    if (file_size == -1L) {
        fprintf(stderr, "Error determining file size.\n");
        fclose(f_in);
        return EXIT_FAILURE;
    }

    // Check that file size is a multiple of sizeof(int8_t)
    if (file_size % sizeof(int8_t) != 0) {
        fprintf(stderr, "Error: File size (%ld bytes) is not a multiple of the size of int8_t (%zu bytes).\n", 
                file_size, sizeof(int8_t));
        fclose(f_in);
        return EXIT_FAILURE;
    }

    // Calculate total elements
    uint64_t total_elements = (uint64_t)file_size / sizeof(int8_t);

    // Check that total elements is a multiple of N
    if (total_elements % opts.N != 0) {
        fprintf(stderr, "Error: Total elements (%lu) is not a multiple of N (%u).\n", total_elements, opts.N);
        fclose(f_in);
        return EXIT_FAILURE;
    }

    // Calculate initial K (number of configurations)
    uint64_t initial_K = total_elements / opts.N;

    if (opts.verbose) {
        printf("Reading %lu configurations of length %u from '%s'\n", initial_K, opts.N, opts.binary_file);
    }

    // Open the output file if in 'file' mode
    FILE *f_out = NULL;
    if (strcmp(opts.mode, "file") == 0) {
        __fopen(&f_out, opts.output_file, "wb");
    }

    // Process all configurations until EOF
    if (!process_configurations(f_in, f_out, opts.mode, opts.N, opts.verbose)) {
        fclose(f_in);
        if (f_out) fclose(f_out);
        return EXIT_FAILURE;
    }

    // Clean up
    fclose(f_in);
    if (f_out) fclose(f_out);

    if (opts.verbose) {
        printf("Successfully processed all configurations.\n");
    }

    return EXIT_SUCCESS;
}
