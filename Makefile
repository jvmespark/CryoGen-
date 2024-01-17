OBJS := $(wildcard *.cpp)
BINS := $(SRCS:%.cpp=%)

CC = g++ -w
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