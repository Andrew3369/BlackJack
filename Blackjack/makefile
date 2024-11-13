# Compiler Type
CXX := g++

# Compiler Flags
CXXFLAGS := -std=c++11 -Wall -Iinc

# Source files directory
SRC_DIR := src

# Include files directory
INC_DIR := inc

# Object files directory
OBJ_DIR := obj
# Bin folder directory (exe file)
BIN_DIR := bin

# Output executable
EXEC := $(BIN_DIR)/BlackJack

# Get all the source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file names from source file names
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile each source file into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)