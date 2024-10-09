# ============================
# Variable Definitions
# ============================

# Root directories
SRC_DIR := src
LIB_DIR := $(SRC_DIR)/lib
SFMT_DIR := $(LIB_DIR)/SFMT

# Source files
SRCS := $(SRC_DIR)/markov-ising1d.c \
        $(LIB_DIR)/options.c \
        $(LIB_DIR)/utils.c \
        $(LIB_DIR)/sfmtrng.c \
        $(SFMT_DIR)/SFMT.c  # Add this line

# Object files
OBJS := $(SRCS:.c=.o)

# Compiler and flags
CC := gcc
LMFLAG := -lm
WALLFLAG := -Wall
WEXTFLAG := -Wextra
DSFMTFLAG := -DSFMT_MEXP=19937
CFLAGS := $(WALLFLAG) $(WEXTFLAG) -I$(LIB_DIR) -I$(SFMT_DIR) -g $(DSFMTFLAG) -fPIC

# Target executable name
TARGET := markov-ising1d

# ============================
# Default Target
# ============================

all: $(TARGET)

# ============================
# Linking
# ============================

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LMFLAG)

# ============================
# Compilation
# ============================

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ============================
# Clean Up
# ============================

clean:
	rm -f $(OBJS) $(TARGET)

# ============================
# Phony Targets
# ============================

.PHONY: all clean
