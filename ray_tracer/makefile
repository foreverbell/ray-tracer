# Project Name (executable)
PROJECT = rt
# Compiler
CC = gcc

# Compiler options during compilation
COMPILE_OPTIONS = `sdl-config --cflags` -g -O2 -Wall -std=c++0x

# Libraries for linking
LIBS = `sdl-config --libs` -lstdc++ -lm -ldl

# Subdirs to search for additional source files
SUBDIRS := $(shell ls -F | grep "\/" )
DIRS := ./ $(SUBDIRS) 
SOURCE_FILES := $(foreach d, $(DIRS), $(wildcard $(d)*.cpp) )

PLY_DIR = ../ply-1.1

# Create an object file of every cpp file
OBJECTS  = $(patsubst %.cpp, %.o, $(SOURCE_FILES)) 
# Extra object files
OBJECTS += $(PLY_DIR)/plyfile.o

# Make $(PROJECT) the default target
all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $(OBJECTS) $(LIBS)

# Compile every cpp file to an object
%.o: %.cpp
	$(CC) -c $(COMPILE_OPTIONS) -o $@ $<

# Extra source files
$(PLY_DIR)/plyfile.o: $(PLY_DIR)/plyfile.c
	$(CC) -c $(COMPILE_OPTIONS) -o $@ $<

# Clean
clean:
	rm -f $(PROJECT) $(OBJECTS)

.PHONY: clean
