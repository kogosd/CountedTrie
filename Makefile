# Makefile for compiling a single C++ file

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++2a

# Source file and output executable
SRC := countedtrie.cpp 
EXECUTABLE := countedtrie
HEADER := util.h

# Default target
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean target to remove the executable
clean:
	rm -f $(EXECUTABLE)

run:
	./$(EXECUTABLE) $(ARG)
