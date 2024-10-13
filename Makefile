# ============================
# Variable Definitions
# ============================

# Root directories
SRC_DIR := src
LIB_DIR := $(SRC_DIR)/lib
SFMT_DIR := $(LIB_DIR)/SFMT
DATA_DIR := data

# Source files
SRCS := $(SRC_DIR)/markov-ising1d.c \
		$(LIB_DIR)/options.c \
		$(LIB_DIR)/utils.c \
		$(LIB_DIR)/sfmtrng.c \
		$(SFMT_DIR)/SFMT.c  # Add this line
SRC2 := $(SRC_DIR)/markov-ising1d_reader.c \
		$(LIB_DIR)/options_reader.c \
		$(LIB_DIR)/utils.c \
		$(LIB_DIR)/sfmtrng.c \
		$(SFMT_DIR)/SFMT.c
# Object files
OBJS := $(SRCS:.c=.o)
OBJS2 := $(SRC2:.c=.o)
# Compiler and flags
CC := gcc
LMFLAG := -lm
WALLFLAG := -Wall
WEXTFLAG := -Wextra
DSFMTFLAG := -DSFMT_MEXP=19937
CFLAGS := $(WALLFLAG) $(WEXTFLAG) -I$(LIB_DIR) -I$(SFMT_DIR) -g $(DSFMTFLAG) -fPIC

# Target executable name
TARGET := markov-ising1d
TARGET2 := markov-ising1d_reader

# ============================
# Default Target
# ============================

all: $(TARGET) $(TARGET2) $(DATA_DIR)

# ============================
# Linking
# ============================

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LMFLAG)

$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $^ $(LMFLAG)

# Rule to create the directory
$(DATA_DIR):
	mkdir -p $(DATA_DIR)

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
	rm -f $(OBJS2) $(TARGET2)

# ============================
# Phony Targets
# ============================

.PHONY: all clean
