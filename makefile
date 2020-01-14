#OBJS specifies which files to compile as part of the project
OBJS = main.cc Game.cc TextureManager.cc GameObject.cc Map.cc Vector2D.cc Collision.cc ECS/ECS.cc

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -g -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
# -l means we are linking the SDL2 library
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the naem of our executable
OBJ_NAME = main 

#this is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)

tags: $(SRCS) makefile
	rm tags
	-ctags -R
