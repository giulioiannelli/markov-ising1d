#include "utils.h"
/* @brief Convert a string to a 32-bit unsigned integer with error checking.
 * If the conversion fails or the input contains invalid characters, print an error message and exit the program.
 * @param inpt: input string to be converted
 * @param base: numerical base for conversion
 * @return uint32_t: the converted unsigned integer
 */
uint32_t strtoul_check(char *inpt, int base)
{
    char *endptr;
    uint32_t tmp;
    tmp = strtoul(inpt, &endptr, base);
    if (*endptr != '\0' || errno != 0)
    {
        printf(ERR_MESSAGE_CONV MESSAGE_EXIT, endptr);
        exit(EXIT_FAILURE);
    }
    return tmp;
}
/* @brief Convert a string to a double with error checking.
 * If the conversion fails or the input contains invalid characters, print an error message and exit the program.
 * @param inpt: input string to be converted
 * @return double: the converted double value
 */
double strtodb_check(char *inpt)
{
    char *endptr;  // Define endptr locally within the function
    double tmp;
    tmp = strtod(inpt, &endptr);
    if (*endptr != '\0' || errno != 0)
    {
        fprintf(stderr, ERR_MESSAGE_CONV MESSAGE_EXIT, endptr);
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
uint64_t strtoull_check(char *inpt, int base)
{
    char *endptr;
    uint64_t tmp;
    tmp = strtoull(inpt, &endptr, base);
    if (*endptr != '\0' || errno != 0)
    {
        fprintf(stderr, ERR_MESSAGE_CONV MESSAGE_EXIT, endptr);
        exit(EXIT_FAILURE);
    }
    return tmp;
}
/**
 * @brief Checks the PFLIP condition and exits if the condition is not met.
 *
 * @param N  A 32-bit unsigned integer.
 * @param T  A double representing temperature or another relevant parameter.
 */
void check_pflip(uint32_t N, double T) {
    if (PFL1P < PTHRESH) {
        exit(EXIT_SUCCESS);
    }
}