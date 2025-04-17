# Compiler and flags
CXX := g++
CFLAGS := -Wall -Wextra

# Libs
LIB := -lSDL2main -lSDL2 -lSDL2_image
INCLUDE := include 

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib

# Create a list of all .c files in SRC_DIR
SRCS := $(wildcard $(SRC_DIR)/*.cpp )

# Create a list of .o files in OBJ_DIR with same names
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary
TARGET := $(BIN_DIR)/main

# Default target
all: $(TARGET)

format: $(SRCS) 
	@clang-format -i $^
	@find include/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i

lib: $(OBJS)
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB_DIR)/libchicagosdl-dev.a $^

# Linking
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CFLAGS) -o $@ $^ $(LIB)
	@echo "LD " $^

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CFLAGS) -c $< -o $@ -I$(INCLUDE)
	@echo "CXX " $<

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

.PHONY: all clean

