CXX = g++ 
CC = gcc
CXXFLAGS = -Wall -Wextra -static -Ilib
CCFLAGS = -Wall -Wextra -static -Ilib

TARGET = lox

SRC_DIR = src
LIB_DIR = lib

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# SRCS = $(wildcard $(SRC_DIR)/*.c) solo por c

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=%.o)
# OBJS = $(SRCS:$(SRC_DIR)/%.c=%.o) 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c  $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean