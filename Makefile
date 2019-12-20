CC := g++
CFLAGS := -std=c++14 -Wall -Wextra -Wpedantic -Ofast -funroll-loops -finline-functions
TARGET := bigint-exp-evaluator

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: clean
clean: $(TARGET)
	rm -rf *.o
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
