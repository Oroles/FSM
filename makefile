# Project Name (executable)
PROJECT = demoproject
# Compiler
CC = g++-4.9

# Run Options       
COMMANDLINE_OPTIONS =

# Compiler options during compilation
COMPILE_OPTIONS = -Wall -std=c++11

#Header include directories
HEADERS =
#Libraries for linking
LIBS = -lwiringPi

# Dependency options
DEPENDENCY_OPTIONS = -std=c++11 -MM

#-- Do not edit below this line --

# Subdirs to search for additional source files
SUBDIRS := $(shell ls -F | grep -v 'tests' | grep '[a-zA-Z]*[\/]' )
DIRS := ./ $(SUBDIRS)
SOURCE_FILES := $(foreach d, $(DIRS), $(wildcard $(d)*.cpp) )

# Create an object file of every cpp file
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCE_FILES))

# Dependencies
DEPENDENCIES = $(patsubst %.cpp, %.d, $(SOURCE_FILES))

# Create .d files
%.d: %.cpp
	$(CC) $(DEPENDENCY_OPTIONS) $< -MT "$*.o $*.d" -MF $*.d

all: debug

release: COMPILE_OPTIONS += -DNDEBUG
release: debug

# Make $(PROJECT) the default target
debug: $(DEPENDENCIES) $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -std=c++11 -o $(PROJECT) $(OBJECTS) $(LIBS)

# Include dependencies (if there are any)
ifneq "$(strip $(DEPENDENCIES))" ""
    include $(DEPENDENCIES)
endif

# Compile every cpp file to an object
%.o: %.cpp
	$(CC) -c $(COMPILE_OPTIONS) -o $@ $< $(HEADERS)

# Build & Run Project
run: $(PROJECT)
	./$(PROJECT) $(COMMANDLINE_OPTIONS)

# Clean & Debug
.PHONY: makefile-debug
makefile-debug:

.PHONY: clean
clean:
	rm -f $(PROJECT) $(OBJECTS)

.PHONY: depclean
depclean:
	rm -f $(DEPENDENCIES)

clean-all: clean depclean
