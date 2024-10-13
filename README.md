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
In order to make the executable for running the C programs just run
```
make all
```
in the root directory.

## running the generator program
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
	-r, --rand_seed			Set the seed randomly.

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
2. `o` is the output base file name which will be in the format
    ```
    <file-path><file-name>_T%.3g_K%lu_[%#.8X_%#.8X].bin
    ```
    where numbers in squared braces are the two selected seeds for proper program randomization.
3. `r` is the option setting the seed randomly, ensuring proper sampling.
4. `v` activate verbose mode, printing 

## running the reader program
A reader that turns binary files produced by `markov-ising1d` is available and is compiled by `make all`. It is called `markov-ising1d_reader.c` and will compile to `markov-ising1d_reader` unless differently specified. Running the helper 
```
$ ./markov-ising1d_reader -h
Usage: ./markov-ising1d_reader [OPTIONS] binary_file mode N [output_file]

Positional Arguments:
  binary_file	Path to the binary file containing configurations. (mandatory)
  mode		Operation mode ('file' to write to a text file, 'stdout' to print to stdout). (mandatory)
  N		Length of each configuration (number of +1/-1 entries). (mandatory)

Options:
  -o, --output_file	Path to the output text file.
  -h, --help		Display this help message.
  -v, --verbose		Enable verbose mode.
```
## minimal example
The following code produce a txt with $N\times K=1000\times 1000$ columns per rows with each of the $K$ configuration (rows) and respective $N$ entries (cols). 
```
$ ./markov-ising1d -k 1000 -r 1000 2.2
$ ./markov-ising1d_reader --output="data/read_vals.txt" 'data/N1000/ising1d_T2.2_K1000_[0X67088FD3_0X00034269].bin' file 1000
```
## the python reader
Alongside with C programs there is a python reader.
```
$ python src/binary_reader.py -h
usage: binary_reader.py [-h] [-o OUTPUT] [-s SHAPE [SHAPE ...]] [--format {txt,csv}] filename {numpy,struct,mmap}

Read binary configuration files containing int8_t data using numpy, struct, or mmap. Optionally reshape the data and either print to screen or write to an
output file.

positional arguments:
  filename              Path to the binary file to be read.
  {numpy,struct,mmap}   Method to read the binary file: "numpy", "struct", or "mmap".

options:
  -h, --help            show this help message and exit
  -o, --output OUTPUT   Output filename to write the data. If not provided, data will be printed to the screen.
  -s, --shape SHAPE [SHAPE ...]
                        Shape to reshape the data (e.g., --shape 100 100 for a 100x100 array). Provide multiple integers for higher dimensions.
  --format {txt,csv}    Output file format: "txt" for plain text or "csv" for CSV format. Default is "txt".
```
which can e.g. be used as 
```
$ python src/binary_reader.py "data/N1000/ising1d_T2.2_K1000_[0X67088FD3_0X00034269].bin" numpy --output="data/read_withpy.txt" --shape 1000 1000
INFO: Reading file with numpy...
INFO: File successfully read with numpy.
INFO: Reshaping data to shape (1000, 1000)...
INFO: Data successfully reshaped to (1000, 1000).
INFO: Data successfully written to 'data/read_withpy.txt'.
```