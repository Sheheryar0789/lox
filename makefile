TARGET   = lox.exe

CXX      ?= g++
CXXFLAGS ?= -static -std=c++17 -Wall -Wextra -Ilib 

SRCS = $(wildcard *.cpp) $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)