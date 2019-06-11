CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
LDFLAGS  := -lsfml-graphics \
            -lsfml-system \
            -lsfml-window \
            -lpthread

bin/cppbob: $(wildcard src/*.cpp)
	@test -d bin || mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
