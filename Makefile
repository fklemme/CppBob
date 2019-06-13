# Settings
PROGRAM  ?= cppbob
BUILDDIR ?= build
BINDIR   ?= bin

# Compiler flags
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
LDFLAGS  := -lsfml-graphics \
            -lsfml-system \
            -lsfml-window \
            -lpthread

HEADERS := $(wildcard src/*.hpp)
SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# Default "all" target
.DEFAULT_GOAL := all
.PHONY: all
all: $(BINDIR)/$(PROGRAM)

# Build program
$(BINDIR)/$(PROGRAM): $(OBJECTS)
	@test -d $(BINDIR) || mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build object files
$(BUILDDIR)/%.o: src/%.cpp
	@test -d $(dir $@) || mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<

# Dependency handling
-include $(patsubst src/%.cpp,$(BUILDDIR)/%.d,$(SOURCES))

# Clean target
PHONY: clean
clean:
	rm -rf $(BUILDDIR)

# Clang format
.PHONY: format
format:
	clang-format -i -style=file $(HEADERS) $(SOURCES)

# Clang Tidy
CHECKS := cppcoreguidelines-*,modernize-*,readability-*
# Remove some unwanted checks
CHECKS := $(CHECKS),-readability-braces-around-statements
CHECKS := $(CHECKS),-readability-uppercase-literal-suffix
# Magic numbers are fine for now
CHECKS := $(CHECKS),-readability-magic-numbers
CHECKS := $(CHECKS),-cppcoreguidelines-avoid-magic-numbers
.PHONY: tidy
tidy:
	clang-tidy -checks=$(CHECKS) -header-filter="src/" $(SOURCES) -- $(CXXFLAGS)
