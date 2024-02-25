# Compilers
CC          := g++ -std=c++17
DGEN        := doxygen

# The Target Binary Program
TARGET      := test

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := .
INCDIR      := .
BUILDDIR    := ./build
TARGETDIR   := ./bin
SRCEXT      := cc

# Flags, Libraries and Includes
CFLAGS      := -g
LIB         := -lgtest -lgtest_main -lpthread
INC         := -I$(INCDIR)
INCDEP      := -I$(INCDIR)

# Google Test Library Directory
GTEST_LIB_DIR := /opt/homebrew/Cellar/googletest/1.14.0/lib

# Files
DGENCONFIG  := docs.config
HEADERS     := $(wildcard *.h)
SOURCES     := $(wildcard *.$(SRCEXT))
OBJECTS     := $(patsubst %.$(SRCEXT), $(BUILDDIR)/%.o, $(notdir $(SOURCES)))

# Default Make
all: directories $(TARGETDIR)/$(TARGET)

# Remake
remake: cleaner all

# Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

# Make the documentation
$(DGENCONFIG):
	$(DGEN) -g $(DGENCONFIG)

docs: $(SOURCES) $(HEADERS) $(DGENCONFIG)
	$(DGEN) $(DGENCONFIG)

# Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)/*.o

# Full Clean, Objects and Binaries
spotless: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET) $(DGENCONFIG) *.db
	@$(RM) -rf build bin html latex

# Link
$(TARGETDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB) -L$(GTEST_LIB_DIR)

# Compile
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY: directories remake clean cleaner apidocs $(BUILDDIR) $(TARGETDIR)
