#
# Basic Makefile
#
TARGET   = rxml 
CC       = g++
CFLAGS   = -c -g -Wall -std=c++0x # -ansi -pedantic-errors
OFLAGS   = -pthread
SOURCES  := rxml.cpp xmlprocessor.cpp
INCLUDES := xmlprocessor.h
OBJECTS  := $(SOURCES:.cpp=*.o)

#SOURCES  := $(wildcard *.cpp)
#INCLUDES := $(wildcard *.hpp)
#OBJECTS  := $(SOURCES:.cpp=*.o)
 
all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(OFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(SOURCES) $(INCLUDES)
		$(CC) $(CFLAGS) $(SOURCES)

clean:
		rm -rf *o $(TARGET) 
        
