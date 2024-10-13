#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h> 
#include <sys/types.h>
#ifdef _WIN32
    #include <direct.h> 
    #define mkdir_p _mkdir
    #define PATH_SEPARATOR "\\"
    #define PATH_SEPARATOR_C '\\'
#else
    #define PATH_SEPARATOR_C '/'
    #define PATH_SEPARATOR "/"
#endif
#include <errno.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "sfmtrng.h"

#define J 1
#define k_B 1
#define PFLIP   (0.5 * (tanh(J / (k_B*T)) + 1.0))
#define PFL1P   (1.0 - PFLIP)
#define PTHRESH (1.0 / (double)N)

#define SGN01(x) (x < 0 ? -1 : 1)

#define PS PATH_SEPARATOR
#define PATH_DATA "data"

#define ERR_MESSAGE_ARGS "Error: Expected exactly 2 positional arguments (N and T), but got %d.\n"
#define ERR_MESSAGE_CONV "Conversion failed, got string: %s\n"
#define MESSAGE_EXIT "Exiting program...\n"

extern uint32_t strtoul_check(char *inpt, int base);
extern double strtodb_check(char *inpt);
extern uint64_t strtoull_check(char *inpt, int base);

extern void __fopen(FILE **f, const char *fn, const char *md);

extern void check_pflip(uint32_t N, double T);

long get_file_size(FILE *fp);
// Function to read a single configuration from the binary file
bool read_configuration(FILE *f_in, int8_t *config, uint32_t N);
bool write_configuration_to_file(FILE *f_out, int8_t *config, uint32_t N);
bool print_configuration(int8_t *config, uint32_t N);
bool process_configurations(FILE *f_in, FILE *f_out, const char *mode, uint32_t N, bool verbose);

int mkdir_p_recursive(const char *path, mode_t mode);
int ensure_directory_exists(const char *path, bool verbose);

#endif // UTILS_H