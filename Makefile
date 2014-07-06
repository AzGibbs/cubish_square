CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -DDEBUG
INCLUDES = -I$(HOME)/usr/include
LDFLAGS = -L$(HOME)/usr/lib -L$(HOME)/usr/lib64
LIBS = -lGL -lglfw3 -lGLEW -lm -lXrandr
SOURCES = cube.cpp input.cpp main.cpp renderer.cpp updatecubestate.cpp
OBJECTS = $(patsubst %.cpp, tmp/%.o, $(SOURCES))

all: tmp $(OBJECTS)
	$(CXX) $(OBJECTS) -o cubish_square $(LDFLAGS) $(LIBS)

tmp/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

tmp:
	mkdir tmp

clean:
	rm -rf tmp/
