#ifndef BITMAP_H
#define BITMAP_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bitmap{
const char* filename;
public:
	int w;
	int h;
	Uint32* pixels;
	SDL_Surface* image;
	Bitmap();
	Bitmap(const char* name);
	~Bitmap();
	Uint32* getUV(float u,float v);
};

#endif