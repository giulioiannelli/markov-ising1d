#include "utils.h"
#include "options.h"

#define PROGN "markov-ising1d"
#define NARG 1 + 2

int main(int argc, char *argv[])
{
    __set_seed_SFMT();
    // parse command-line arguments
    Options options;
    if (parse_arguments(argc, argv, &options) != 0) {
        exit(EXIT_FAILURE);
    }
    // decalre variables
    FILE *f_out;
    char buf[256];
    uint32_t N = options.N;
    double T = options.T;
    // check pflip
    check_pflip(N, T);
    // open the file
    sprintf(buf, PATH_DATA );
    // if ((f_out = fopen(buf, "a+b")) == NULL)
    // {
    //     printf(MSGFAIL PFFOPEN "%s" MSGEXIT, buf);
    //     exit(EXIT_FAILURE);
    // }
    // fseek(f_out, 0, SEEK_END);
    // /* generate missingK configuration */
    // for (uint32_t k = 0; k < missingK; k++)
    // {
    //     s = calloc(N, sizeof(*s));
    //     s[0] = SGN01(rnd_dbl() - .5);
    //     for (uint32_t i = 1; i < N; i++)
    //     {
    //         if (rnd_dbl() < PFLIP)
    //             s[i] = s[i - 1];
    //         else
    //             s[i] = -s[i - 1];
    //     }
    //     fwrite(s, sizeof(*s), N, f_out);
    //     free(s);
    // }
    // if (effKNUM < KNUM)
    // {
    //     sprintf(buf2, DIRCFGS P_TYPE _U __NIS__ _U __TIS__ _U __KNUMIS__ EXTBIN,
    //             N, T, KNUM);
    //     if ((rename(buf, buf2)) == 0)
    //     {
    //         fprintf(f_log, PIFRSUC);
    //     }
    //     else
    //     {
    //         fprintf(f_log, MSGFAIL PFUNREN);
    //     }
    // }
    // fclose(f_log);
    // fclose(f_out);
}
 