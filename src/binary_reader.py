import argparse
import os
import sys
from binary_reader_functions import (
    read_with_numpy,
    read_with_struct,
    read_with_mmap,
    print_data,
    write_data_to_file,
    write_data_to_csv,
    reshape_data
)

def parse_arguments():
    """
    Parses command-line arguments.

    :return: Parsed arguments.
    """
    parser = argparse.ArgumentParser(
        description=(
            "Read binary configuration files containing int8_t data using numpy, struct, or mmap. "
            "Optionally reshape the data and either print to screen or write to an output file."
        )
    )
    parser.add_argument(
        'filename',
        type=str,
        help='Path to the binary file to be read.'
    )
    parser.add_argument(
        'mode',
        type=str,
        choices=['numpy', 'struct', 'mmap'],
        help='Method to read the binary file: "numpy", "struct", or "mmap".'
    )
    parser.add_argument(
        '-o', '--output',
        type=str,
        default=None,
        help='Output filename to write the data. If not provided, data will be printed to the screen.'
    )
    parser.add_argument(
        '-s', '--shape',
        type=int,
        nargs='+',
        help='Shape to reshape the data (e.g., --shape 100 100 for a 100x100 array). Provide multiple integers for higher dimensions.'
    )
    parser.add_argument(
        '--format',
        type=str,
        choices=['txt', 'csv'],
        default='txt',
        help='Output file format: "txt" for plain text or "csv" for CSV format. Default is "txt".'
    )
    return parser.parse_args()

def main():
    args = parse_arguments()

    # Validate input file
    if not os.path.isfile(args.filename):
        print(f"Error: File '{args.filename}' does not exist.")
        sys.exit(1)

    # Read data based on mode
    if args.mode == 'numpy':
        data = read_with_numpy(args.filename)
    elif args.mode == 'struct':
        data = read_with_struct(args.filename)
    elif args.mode == 'mmap':
        data = read_with_mmap(args.filename)
    else:
        print(f"Error: Invalid mode '{args.mode}'. Choose 'numpy', 'struct', or 'mmap'.")
        sys.exit(1)

    # Reshape data if shape is provided
    if args.shape:
        shape = tuple(args.shape)
        data = reshape_data(data, shape)

    # Handle output
    if args.output:
        if args.format == 'txt':
            write_data_to_file(data, args.output)
        elif args.format == 'csv':
            write_data_to_csv(data, args.output)
    else:
        print_data(data)

if __name__ == "__main__":
    main()
