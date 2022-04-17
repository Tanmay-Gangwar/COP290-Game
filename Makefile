# #OBJS specifies which files to compile as part of the project
# OBJS = main.cpp

# #CC specifies which compiler we're using
# CC = g++

# #COMPILER_FLAGS specifies the additional compilation options we're using
# # -w suppresses all warnings
# COMPILER_FLAGS = -w

# #LINKER_FLAGS specifies the libraries we're linking against
# LINKER_FLAGS = -lSDL2 -lSDL2_image

# #OBJ_NAME specifies the name of our exectuable
# OBJ_NAME = main.out

# #This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


CC = g++
CLIENT_OBJ = main.cpp
CLIENT_FLAGS = -w -pthread -lSDL2 -lSDL2_image
CLIENT_OUT = main.out

SERVER_OBJ = server.cpp
SERVER_FLAGS = -w -pthread
SERVER_OUT = server.out

all:
	$(CC) $(CLIENT_OBJ) $(CLIENT_FLAGS) -o $(CLIENT_OUT)
	$(CC) $(SERVER_OBJ) $(SERVER_FLAGS) -o $(SERVER_OUT)