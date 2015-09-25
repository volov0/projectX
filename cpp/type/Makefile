#
# Basic Makefile
#
TARGET   = typecast 
CC       = g++
CFLAGS   = -c -g -Wall -std=c++0x # -ansi -pedantic-errors
SOURCES  := typecast.cpp
INCLUDES := 
OBJECTS  := $(SOURCES:.cpp=*.o)

#SOURCES  := $(wildcard *.cpp)
#INCLUDES := $(wildcard *.hpp)
#OBJECTS  := $(SOURCES:.cpp=*.o)
 
all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(SOURCES) $(INCLUDES)
		$(CC) $(CFLAGS) $(SOURCES)

clean:
		rm -rf *o $(TARGET) 
        
