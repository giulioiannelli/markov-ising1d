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
    #define PATH_SEPARATOR '\\'
#else
    #define PATH_SEPARATOR '/'
#endif
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include "sfmtrng.h"

#define J 1
#define k_B 1
#define PFLIP   (0.5 * (tanh(J / (k_B*T)) + 1.0))
#define PFL1P   (1.0 - PFLIP)
#define PTHRESH (1.0 / (double)N)

#define SGN01(x) (x < 0 ? -1 : 1)

#define PATH_DATA "data/"

#define ERR_MESSAGE_ARGS "Error: Expected exactly 2 positional arguments (N and T), but got %d.\n"
#define ERR_MESSAGE_CONV "Conversion failed, got string: %s\n"
#define MESSAGE_EXIT "Exiting program...\n"

extern uint32_t strtoul_check(char *inpt, int base);
extern double strtodb_check(char *inpt);
extern uint64_t strtoull_check(char *inpt, int base);

extern void __fopen(FILE **f, const char *fn, const char *md);

extern void check_pflip(uint32_t N, double T);

int mkdir_p_recursive(const char *path, mode_t mode);
int ensure_directory_exists(const char *path);

#endif // UTILS_H