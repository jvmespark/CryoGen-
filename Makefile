OBJS := $(wildcard *.cpp networking/*.cpp)
BINS := $(SRCS:%.cpp=%)

CC = g++ -std=c++17 -O2 -w
COUNT = cloc
LD_FLAGS = glad.c -ldl -lglfw -lz -lglut -lGL -lGLU -lSDL2

OBJ_NAME = main.exe

.PHONY: build clean

build : ${BINS}
	$(CC) $(OBJS) $(LD_FLAGS) -o $(OBJ_NAME)

run : ${BINS}
	$(CC) $(OBJS) $(LD_FLAGS) -o $(OBJ_NAME)
	./${OBJ_NAME}

clean:
	rm -f $(OBJ_NAME)