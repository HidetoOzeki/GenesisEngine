CC = g++
SRC = src/GenesisEngine.cpp src/Screen3D.cpp src/Screen.cpp src/Bitmap.cpp src/Camera.cpp src/Model.cpp
OBJ = GenesisEngine.o Screen.o Bitmap.o Camera.o Model.o Screen3D.o
LIB = lib/libGenesisEngine.a

INCLUDE = include


all : $(SRC)
		$(CC) -c $(SRC) -I $(INCLUDE)
		mkdir -p lib
		ar rvs $(LIB) $(OBJ)
		rm $(OBJ)