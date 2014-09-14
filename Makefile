CXX = clang++-3.5
CXXFLAGS = -g -std=c++14 -Wall -fstrict-aliasing
INCLUDES =
LDFLAGS =
LIBS = -lGL -lGLEW -lm -lglfw
SOURCES = cube.cpp input.cpp main.cpp physics.cpp renderer.cpp updatecubestate.cpp
OBJECTS = $(patsubst %.cpp, tmp/%.o, $(SOURCES))

all: tmp $(OBJECTS)
	$(CXX) $(OBJECTS) -o cubish_square $(LDFLAGS) $(LIBS)

tmp/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

tmp:
	mkdir tmp

clean:
	rm -rf tmp/
