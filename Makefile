CXX = /usr/not-backed-up/gcc-build/bin/g++
CXXFLAGS = -g -std=c++11 -Wall -fstrict-aliasing
INCLUDES = 
LDFLAGS = 
LIBS = -lGL -lGLEW -lm -lXrandr `pkg-config glfw3 --libs`
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
