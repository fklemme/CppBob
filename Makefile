CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
LDFLAGS  := -lsfml-graphics \
            -lsfml-system \
            -lsfml-window \
            -lpthread

test: $(wildcard src/*.cpp)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
