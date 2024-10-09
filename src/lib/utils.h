#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include "sfmtrng.h"

#define J 1
#define k_B 1
#define PFLIP   (0.5 * (tanh(J / (k_B*T)) + 1.0))
#define PFL1P   (1.0 - PFLIP)
#define PTHRESH (1.0 / (double)N)

#define PATH_DATA "data/"

#define ERR_MESSAGE_ARGS "Wrong number of arguments passed, expected: %d\n"
#define ERR_MESSAGE_CONV "Conversion failed, got string: %s\n"
#define MESSAGE_EXIT "Exiting program...\n"

uint32_t strtoul_check(char *inpt, int base);
double strtodb_check(char *inpt);
uint64_t strtoull_check(char *inpt, int base);
void check_pflip(uint32_t N, double T);

#endif // UTILS_H