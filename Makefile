CXX = g++
CXXFLAGS = -Wall -Werror -lglut -lGL #-lGLU

all: main

main:
	$(CXX) $(CXXFLAGS) hello.cpp
