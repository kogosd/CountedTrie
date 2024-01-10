# Makefile for compiling a single C++ file

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++2a

# Source file and output executable
SRC := countedtrie.cpp test.cpp
EXECUTABLE := countedtrie
HEADER := util.h
OBJ := $(SRC:.cpp=.o)  # Object files


# Default target
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(SRC) 
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to generate object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove the executable
clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARG)
