CC = g++
SRC = src/GenesisEngine.cpp src/RNG.cpp src/gfx/Screen.cpp src/gfx/Bitmap.cpp
OBJ = GenesisEngine.o Screen.o RNG.o Bitmap.o

LIBFILE = lib/libGenesis.a

INCLUDE = -IC:\MinGW_lib\i686-w64-mingw32\include -IC:\Users\Ozeki\Dev\GenesisEngine\include

all : $(SRC)
	g++ -c $(SRC) $(INCLUDE)
	ar crf $(LIBFILE) $(OBJ)

clean:
	rm -f *.o