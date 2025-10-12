# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror -O2
SRCS := book.cpp search.cpp SearchNewBooks.cpp
TARGET := SearchNewBooks

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Build test executable
tests: book.cpp search.cpp tests.cpp
	$(CXX) $(CXXFLAGS) book.cpp search.cpp tests.cpp -o tests

clean:
	rm -f $(TARGET) *.o *.dat

.PHONY: all clean