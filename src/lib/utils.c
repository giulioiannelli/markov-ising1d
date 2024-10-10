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
    if(tmp[len - 1] == PATH_SEPARATOR)
        tmp[len - 1] = '\0';

    for(p = tmp + 1; *p; p++) {
        if(*p == PATH_SEPARATOR) {
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
            *p = PATH_SEPARATOR;
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
int ensure_directory_exists(const char *path) {
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
            printf("Directory created: %s\n", path);
            return 0;
        } else {
            // Other errors
            perror("stat");
            fprintf(stderr, "Error: Failed to stat directory %s: %s\n", path, strerror(errno));
            return -1;
        }
    }
}
