CC = g++
CFLAGS = -std=c++14 -Wall

# List of source files
SRCS = main.cpp
HEADERS = $(wildcard *.hpp)

# Path to the chrono.hpp library
CHRONO_LIB = /home/gabrpasca/pacs-examples/Examples/src/Utilities/chrono.hpp

# Name of the executable
TARGET = pacs24

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS) $(CHRONO_LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)