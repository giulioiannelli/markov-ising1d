# markov-ising1d
Repository containing a short C code to generate independent 1D Ising model configuration at given temperature (i.e. with the same correlation length).

## initialization
This repo is compatible with Linux based operating systems.

A conda environment comes along the code for consistency in C compiler, which is `gcc 11.4.0`, and for python, `3.12`. Moreover the conda environment locally install `make` tool. If all of the above requirements are satisfied there is no use for the next step and one can jump directly to section [Go to Real Cool Heading section](#compiling-c-programs).

### conda environment setup
In order to setup the conda environment `(markov-ising1d)` you can use the `conda` utility as
```
conda env create -f environment.yml
conda activate markov-ising1d
```

### compiling C programs 
In order to make the executable for running the C programs just run
```
make all
```
in the root directory. This process will also create directory `data` in the `markov-ising1d` folder which is needed by the programs.

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

## why do we use markov chain to generate ising 1d patterns
In the one-dimensional (1D) Ising model, each spin interacts only with its nearest neighbors. This simplicity allows us to generate spin configurations efficiently using a Markov process without the need for thermalizing the entire linear chain. Below, I provide a formal explanation with relevant formulas to demonstrate why the provided generation process correctly samples configurations from the Boltzmann distribution of the 1D Ising model.

### The 1D Ising Model Basics

The Hamiltonian $H$ for the 1D Ising model with nearest-neighbor interactions is given by:
$$
H(\mathbf{s}) = -J \sum_{i=1}^{N-1} s_i s_{i+1}
$$
where:
- $\mathbf{s} = (s_1, s_2, \dots, s_N)$ is a spin configuration.
- $s_i \in \{+1, -1\}$ represents the spin at site $ i $.
- $J$ is the interaction strength between neighboring spins.
- $N$ is the total number of spins.

The Boltzmann distribution for this system at temperature $T$ is:
$$
P(\mathbf{s}) = \frac{1}{Z} e^{-\beta H(\mathbf{s})} = \frac{1}{Z} \exp\left(\beta J \sum_{i=1}^{N-1} s_i s_{i+1}\right)
$$
where $\beta = \frac{1}{k_B T}$ and $ Z $ is the partition function ensuring normalization.

### Factorization of the Boltzmann Distribution

Due to the nearest-neighbor interactions in the 1D Ising model, the joint probability $P(\mathbf{s})$ can be factorized into conditional probabilities:
$$
P(\mathbf{s}) = P(s_1) \prod_{i=2}^N P(s_i \mid s_{i-1})
$$
This factorization leverages the Markov property, where each spin $s_i$ depends only on its immediate predecessor $s_{i-1}$.

### Determining the Conditional Probabilities

To match the Boltzmann distribution, the conditional probability $P(s_i \mid s_{i-1})$ must satisfy:
$$
\frac{P(s_i = s_{i-1} \mid s_{i-1})}{P(s_i = -s_{i-1} \mid s_{i-1})} = \exp\left(2\beta J s_i s_{i-1}\right)
$$
Since $s_i s_{i-1} = \pm 1$, when $s_i=s_{i-1}$ this simplifies to:
$$
\frac{P(s_i = s_{i-1} \mid s_{i-1})}{P(s_i = -s_{i-1} \mid s_{i-1})} = \exp(2\beta J)
$$
Let $P_{\text{flip}} = P(s_i = s_{i-1} \mid s_{i-1})$. Then:
$$
\frac{P_{\text{flip}}}{1 - P_{\text{flip}}} = \exp(2\beta J)
$$

Solving for $P_{\text{flip}}$:
$$
P_{\text{flip}} = \frac{\exp(2\beta J)}{1 + \exp(2\beta J)}
$$
Using the hyperbolic tangent function identity:
$$
\frac{\tanh(x) + 1}{2} = \frac{\exp(2x)}{1 + \exp(2x)}
$$
Substituting $x = \beta J$:
$$
P_{\text{flip}} = \frac{\tanh(\beta J) + 1}{2} = \frac{1}{2} \left( \tanh\left(\frac{J}{k_B T}\right) + 1 \right)
$$

This matches the definition in the code.

### The Generation Process as a Markov Chain

The provided generation process implements the following steps:

1. **Initialization**: 
   - The first spin $s_0$ is randomly set to $+1$ or $-1$ with equal probability:
     $$
     P(s_0) = \frac{1}{2}, \quad P(s_0 = +1) = P(s_0 = -1) = \frac{1}{2}
     $$
   
2. **Sequential Spin Generation**:
   - For each subsequent spin $s_i$ ($i = 1, 2, \dots, N-1$):
     $$
     s_i = 
     \begin{cases} 
     s_{i-1} & \text{with probability } P_{\text{flip}} \\
     -s_{i-1} & \text{with probability } 1 - P_{\text{flip}}
     \end{cases}
     $$
   
This process effectively constructs a Markov chain where each spin depends only on its immediate predecessor, adhering to the factorization of the Boltzmann distribution.

### **6. Summary**

- **Markov Property**: In 1D, each spin interacts only with its nearest neighbor, allowing the use of a Markov process.
- **Conditional Probabilities**: By setting $P_{\text{flip}} = \frac{1}{2} \left( \tanh\left(\frac{J}{k_B T}\right) + 1 \right)$, the conditional probabilities align with the Boltzmann distribution.
- **Sequential Generation**: Spins are generated sequentially, ensuring that the overall configuration probability matches $P(\mathbf{s})$.