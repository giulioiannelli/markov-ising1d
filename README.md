# markov-ising1d
Repository containing a short C code to generate independent 1D Ising model configuration at given temperature (i.e. with the same correlation length).

## initialization
This repo is compatible with Linux based operating systems.

A conda environment comes along the code for consistency in C compiler, which is `gcc 11.4.0`, and for python, `3.12`. Moreover the conda environment locally install `make` tool. If all of the above requirements are satisfied there is no use for the next step and one can jump directly to section [Go to Real Cool Heading section](#compiling-c-programs).

### conda environemnt setup
In order to setup the conda environemnt `(markov-ising1d)` you can use the `conda` utility as
```
conda env create -f environment.yml
```
### compiling C programs 
In order to make the executable for running the C program just run
```
make
```
in the root directory.

## running the program
If you didnt specify a different name during compilation the executable in `markov-ising1d` folder should be `markov-ising1d`. One can visualize an helper for explanation of the parser structure, by executing `markov-ising1d` with the `-h` or `--help` flag. 
```
$ ./markov-ising1d -h
Usage: ./markov-ising1d [OPTIONS] N T
Positional Arguments:
	N			Parameter N. (mandatory)
	T			Parameter T. (mandatory)

Options:
	-h, --help				Display this help message.
	-v, --verbose				Enable verbose mode.
	-k, --conf_num		K		Number of configurations to save. [default: 1]
	-o, --output		FILE		Specify output file. [default: output.txt]
	-r, --rand_seed		SEED		Set the seed randomly.

```
Given a size $N$ of the system and a temperature $T$ the program can be used for generating a number $K$ of Ising 1D configurations patterns. The program actually generates these not by making the Ising model thermalize (slow), but using the correspondence of a simple Markov chain wich the same equilibrium distribution, 

The mandatory arguments are

1. `N` the size of the pattern to generate
2. `T` the temperature of the generated pattern, linked to the correlation length $L$ by relation 
    $$L = -\frac{1}{\ln(\tanh(\beta))},$$ 
    where $\beta = 1/(k_{\rm B}T)$. The correlation between pattern $\mu$ component $\xi_i^\mu$ and component $\xi_j^\mu$ falls off as
    $$\langle\xi_i^\mu\xi_j^\mu\rangle = e^{-\frac{|i-j|}{L}}.$$

Optional arguments allow for customization of the output.

1. `K` is the number of patterns to be generated, $\mu=1, \dots, K$. 
2. `o` is the output file name 

### structure
The program containing the main code is `markov-ising1d.c` under `src`. 