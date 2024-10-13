# binary_reader_functions.py

import numpy as np
import struct
import sys
import csv
import logging

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')

def read_with_numpy(filename):
    """
    Reads a binary file as int8_t using numpy.

    :param filename: Path to the binary file.
    :return: Numpy array of int8 data.
    """
    try:
        logging.info("Reading file with numpy...")
        data = np.fromfile(filename, dtype=np.int8)
        logging.info("File successfully read with numpy.")
        return data
    except Exception as e:
        logging.error(f"Error reading file with numpy: {e}")
        sys.exit(1)

def read_with_struct(filename):
    """
    Reads a binary file as int8_t using struct.

    :param filename: Path to the binary file.
    :return: List of int8 data.
    """
    try:
        logging.info("Reading file with struct...")
        with open(filename, 'rb') as f:
            byte_data = f.read()
            # 'b' format is for signed char (int8)
            data = list(struct.unpack(f'{len(byte_data)}b', byte_data))
        logging.info("File successfully read with struct.")
        return data
    except Exception as e:
        logging.error(f"Error reading file with struct: {e}")
        sys.exit(1)

def read_with_mmap(filename):
    """
    Reads a binary file as int8_t using numpy memory mapping.

    :param filename: Path to the binary file.
    :return: Numpy memmap object of int8 data.
    """
    try:
        logging.info("Reading file with mmap...")
        data = np.memmap(filename, dtype=np.int8, mode='r')
        logging.info("File successfully read with mmap.")
        return data
    except Exception as e:
        logging.error(f"Error reading file with mmap: {e}")
        sys.exit(1)

def print_data(data):
    """
    Prints the data to the screen.

    :param data: Data to be printed.
    """
    if isinstance(data, np.memmap):
        data = np.array(data)  # Convert memmap to numpy array for better display
    print(data)

def write_data_to_file(data, out_file):
    """
    Writes the data to a text file with a progress bar.

    :param data: Data to be written.
    :param out_file: Path to the output file.
    """
    try:
        with open(out_file, 'w') as f:
            if isinstance(data, np.memmap):
                data = np.array(data)
            elif isinstance(data, list):
                data = np.array(data)
            # Write each integer on a new line with a progress bar
            for item in data:
                f.write(f"{item}\n")
        logging.info(f"Data successfully written to '{out_file}'.")
    except Exception as e:
        logging.error(f"Error writing data to file: {e}")
        sys.exit(1)

def write_data_to_csv(data, out_file):
    """
    Writes the data to a CSV file.

    :param data: Numpy array or list of data.
    :param out_file: Path to the output CSV file.
    """
    try:
        with open(out_file, 'w', newline='') as f:
            writer = csv.writer(f)
            if isinstance(data, list):
                data = np.array(data)
            if isinstance(data, np.memmap):
                data = np.array(data)
            if data.ndim == 1:
                for item in data:
                    writer.writerow([item])
            else:
                writer.writerows(data)
        logging.info(f"Data successfully written to '{out_file}' as CSV.")
    except Exception as e:
        logging.error(f"Error writing data to CSV file: {e}")
        sys.exit(1)

def reshape_data(data, shape):
    """
    Reshapes the data to the specified shape.

    :param data: Numpy array or list of data.
    :param shape: Tuple indicating the desired shape.
    :return: Reshaped data as a NumPy array.
    """
    try:
        logging.info(f"Reshaping data to shape {shape}...")
        if isinstance(data, list):
            data = np.array(data)
        reshaped = data.reshape(shape)
        logging.info(f"Data successfully reshaped to {shape}.")
        return reshaped
    except Exception as e:
        logging.error(f"Error reshaping data: {e}")
        sys.exit(1)
