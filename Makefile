CXX = g++
CC = gcc
CXXFLAGS = -Iinclude -std=c++23
CFLAGS = -Iinclude

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=bin/%.o)
GLAD_OBJ = bin/glad.o

LIBS = -lglfw \
       -lGL \
       -ldl \
       -lpthread

bin/main: $(OBJS) $(GLAD_OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/glad.o: src/glad.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*.o bin/main