# Compiler and flags
CXX := g++
CFLAGS := -Wall -Wextra

# Libs
LIB := -lSDL2main -lSDL2 -lSDL2_image
INCLUDE := -Iinclude 

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Create a list of all .c files in SRC_DIR
SRCS := $(wildcard $(SRC_DIR)/*.cpp )

# Create a list of .o files in OBJ_DIR with same names
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary
TARGET := $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CFLAGS) -o $@ $^ $(LIB)
	@echo "LD " $^

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "CXX " $<

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

