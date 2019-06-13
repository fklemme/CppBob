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
-include $(patsubst src/%.cpp,$(BUILDDIR)/%.d,$(wildcard src/*/*.cpp))

# Clean target
PHONY: clean
clean:
	rm -rf $(BUILDDIR)

# Clang format
.PHONY: format
format:
	clang-format -i -style=file $(HEADERS) $(SOURCES)

# Clang Tidy - Removed some rules because...
#   - cppcoreguidelines-pro-bounds-array-to-pointer-decay: "assert" brings up a lot of these warnings.
#   - readability-braces-around-statements:                I don't like that rule. Let's ignore these.
.PHONY: tidy
tidy:
	clang-tidy -checks=cppcoreguidelines-*,modernize-*,readability-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-readability-braces-around-statements \
	           -header-filter="src/" $(SOURCES) -- $(CXXFLAGS)
