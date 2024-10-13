// utils.c
#include "utils.h"
/* @brief Convert a string to a 32-bit unsigned integer with error checking.
 * If the conversion fails or the input contains invalid characters, print an error message and exit the program.
 * @param inpt: input string to be converted
 * @param base: numerical base for conversion
 * @return uint32_t: the converted unsigned integer
 */
extern uint32_t strtoul_check(char *inpt, int base)
{
    char *endptr;
    uint32_t tmp;
    tmp = strtoul(inpt, &endptr, base);
    if (*endptr != '\0' || errno != 0)
    {
        perror(endptr);
        exit(EXIT_FAILURE);
    }
    return tmp;
}
/* @brief Convert a string to a double with error checking.
 * If the conversion fails or the input contains invalid characters, print an error message and exit the program.
 * @param inpt: input string to be converted
 * @return double: the converted double value
 */
extern double strtodb_check(char *inpt)
{
    char *endptr;  // Define endptr locally within the function
    double tmp;
    tmp = strtod(inpt, &endptr);
    if (*endptr != '\0' || errno != 0)
    {
        perror(endptr);
        exit(EXIT_FAILURE);
    }

    return tmp;
}
/* @brief Convert a string to a 64-bit unsigned integer with error checking.
 * If the conversion fails or the input contains invalid characters, print an error message and exit the program.
 * @param inpt: input string to be converted
 * @param base: numerical base for conversion
 * @return uint64_t: the converted unsigned integer
*/
extern uint64_t strtoull_check(char *inpt, int base)
{
    char *endptr;
    uint64_t tmp;
    tmp = strtoull(inpt, &endptr, base);
    if (*endptr != '\0' || errno != 0)
    {
        perror(endptr);
        exit(EXIT_FAILURE);
    }
    return tmp;
}
/**
 * @brief open a file according to an operative mode allowed by fopen
 * 
 * @param f (FILE **) FILE pointer
 * @param fn (const char *) file name string
 * @param md (const char *) opening mode
 */
extern void __fopen(FILE **f, const char *fn, const char *md)
{
    if ((*f = fopen(fn, md)) == NULL)
    {
        perror(fn);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Checks the PFLIP condition and exits if the condition is not met.
 *
 * @param N  A 32-bit unsigned integer.
 * @param T  A double representing temperature or another relevant parameter.
 */
extern void check_pflip(uint32_t N, double T) {
    if (PFL1P < PTHRESH) {
        exit(EXIT_SUCCESS);
    }
}

// Function to create directories recursively (cross-platform)
int mkdir_p_recursive(const char *path, mode_t mode) {
    char tmp[512];
    char *p = NULL;
    size_t len;

    strncpy(tmp, path, sizeof(tmp));
    tmp[sizeof(tmp) - 1] = '\0';  // Ensure null-termination
    len = strlen(tmp);

    // Remove trailing slash if present
    if(tmp[len - 1] == PATH_SEPARATOR_C)
        tmp[len - 1] = '\0';

    for(p = tmp + 1; *p; p++) {
        if(*p == PATH_SEPARATOR_C) {
            *p = '\0';
#ifdef _WIN32
            if (_mkdir(tmp) != 0) {
#else
            if (mkdir(tmp, mode) != 0) {
#endif
                if (errno != EEXIST) {
                    perror("mkdir");
                    fprintf(stderr, "Error: Failed to create directory %s: %s\n", tmp, strerror(errno));
                    return -1;
                }
            }
            *p = PATH_SEPARATOR_C;
        }
    }

    // Create the final directory
#ifdef _WIN32
    if (_mkdir(tmp) != 0) {
#else
    if (mkdir(tmp, mode) != 0) {
#endif
        if (errno != EEXIST) {
            perror("mkdir");
            fprintf(stderr, "Error: Failed to create directory %s: %s\n", tmp, strerror(errno));
            return -1;
        }
    }

    return 0;
}

// Function to ensure a directory exists (cross-platform)
int ensure_directory_exists(const char *path, bool verbose) {
    struct stat st;

    // Check if the directory exists
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            // Directory exists
            return 0;
        } else {
            // Path exists but is not a directory
            fprintf(stderr, "Error: %s exists but is not a directory.\n", path);
            return -1;
        }
    } else {
        if (errno == ENOENT) {
            // Directory does not exist, attempt to create it recursively
            if (mkdir_p_recursive(path, 0755) != 0) {
                fprintf(stderr, "Error: Failed to create directory %s.\n", path);
                return -1;
            }
            if (verbose) {
                printf("Directory created: %s\n", path);
            }
            return 0;
        } else {
            // Other errors
            perror("stat");
            fprintf(stderr, "Error: Failed to stat directory %s: %s\n", path, strerror(errno));
            return -1;
        }
    }
}
long get_file_size(FILE *fp) {
    long current_pos = ftell(fp);
    if (current_pos == -1L) return -1L;
    if (fseek(fp, 0L, SEEK_END) != 0) return -1L;
    long size = ftell(fp);
    if (size == -1L) return -1L;
    if (fseek(fp, current_pos, SEEK_SET) != 0) return -1L;
    return size;
}


// Function to read a single configuration from the binary file
bool read_configuration(FILE *f_in, int8_t *config, uint32_t N) {
    size_t items_read = fread(config, sizeof(int8_t), N, f_in);
    return items_read == N;
}

// Function to write a configuration to the output file
bool write_configuration_to_file(FILE *f_out, int8_t *config, uint32_t N) {
    if (f_out == NULL || config == NULL) {
        fprintf(stderr, "Invalid file pointer or configuration array.\n");
        return false;
    }

    for (uint32_t i = 0; i < N; i++) {
        // Write each config value followed by a space
        if (fprintf(f_out, "%d ", config[i]) < 0) {
            fprintf(stderr, "Error writing to output file.\n");
            return false;
        }
    }

    // Write a newline at the end
    if (fputc('\n', f_out) == EOF) {
        fprintf(stderr, "Error writing newline to output file.\n");
        return false;
    }

    return true;
}

// Function to print a configuration to stdout
bool print_configuration(int8_t *config, uint32_t N) {
    for (uint32_t i = 0; i < N; i++) {
        printf("%d ", config[i]);
    }
    printf("\n");
    return true;
}

bool process_configurations(FILE *f_in, FILE *f_out, const char *mode, uint32_t N, bool verbose) {
    // Allocate memory for one configuration
    int8_t *config = (int8_t *)malloc(N * sizeof(int8_t));
    if (config == NULL) {
        fprintf(stderr, "Error allocating memory for configuration.\n");
        return false;
    }

    uint64_t processed = 0;

    while (read_configuration(f_in, config, N)) {
        processed++;

        if (strcmp(mode, "file") == 0) {
            if (!write_configuration_to_file(f_out, config, N)) {
                free(config);
                return false;
            }
        } else if (strcmp(mode, "stdout") == 0) {
            if (!print_configuration(config, N)) {
                free(config);
                return false;
            }
        }

        if (verbose && processed % 1000 == 0) {
            printf("Processed %lu configurations.\n", processed);
        }
    }

    // Check for read errors (other than EOF)
    if (ferror(f_in)) {
        fprintf(stderr, "Error reading from binary file.\n");
        free(config);
        return false;
    }

    free(config);

    if (verbose) {
        printf("Total configurations processed: %lu\n", processed);
    }

    return true;
}