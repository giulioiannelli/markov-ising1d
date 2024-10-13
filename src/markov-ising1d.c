// markov-ising1d.c
#include "utils.h"
#include "options.h"

#define PROGN "markov-ising1d"
#define NARG 1 + 2

int main(int argc, char *argv[])
{
    // parse command-line arguments
    Options options;
    if (parse_arguments(argc, argv, &options) != 0) {
        exit(EXIT_FAILURE);
    }
    // decalre variables
    FILE *f_out;
    char buf[1024];
    char buf2[256];
    int8_t *s;
    uint32_t N = options.N;
    uint64_t K = options.conf_num;
    uint32_t seed1 = SEED;
    uint32_t seed2 = SIID;
    double T = options.T;
    // check pflip
    check_pflip(N, T);
    // initialize the SFMT random number generator
    if (options.rand_seed){
        seed1 = CEED;
        seed2 = CIID;
    }
    __set_seed_SFMT(seed1, seed2, options.verbose);
    // open the file
    sprintf(buf2, PATH_DATA PS "N%u" PS, N);
     // Ensure the directory exists
    if (ensure_directory_exists(buf2, options.verbose) != 0) {
        fprintf(stderr, "Failed to ensure directory exists. Exiting.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(buf, "%s%s_T%.3g_K%lu_[%#.8X_%#.8X].bin", 
        buf2, options.output_file, T, K, seed1, seed2);
    __fopen(&f_out, buf, "wb");
    for (uint32_t k = 0; k < K; k++)
    {
        s = calloc(N, sizeof(*s));
        s[0] = SGN01(RNG_dbl() - .5);
        for (uint32_t i = 1; i < N; i++)
        {
            if (RNG_dbl() < PFLIP)
                s[i] = s[i - 1];
            else
                s[i] = -s[i - 1];
        }
        fwrite(s, sizeof(*s), N, f_out);
        free(s);
    }
    fclose(f_out);
}
 