#include "GenesisEngine/gfx/Bitmap.h"
#include <cstring>
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

Bitmap::Bitmap(const char* filename){
    fn = std::string(filename);
    SDL_Surface* image = SDL_LoadBMP(filename);
    if(!image)std::cout << "image file " << filename << " does not exist"<< std::endl;
    w = image->w;
    h = image->h;
    pixels = new int[w*h];
    std::memcpy(pixels,image->pixels,sizeof(int)*w*h);
    SDL_FreeSurface(image);
    std::cout << "Bitmap image ["<< filename << "] successfully loaded" << std::endl;
}

Bitmap::Bitmap(int width,int height){
    w = width;
    h = height;
    pixels = new int[w*h];
    std::cout << "Bitmap image initialized with width and height" << std::endl;
}

Bitmap::~Bitmap(){
    Bitmap::destroy();
}

void Bitmap::destroy(){
    if(!fn.empty())std::cout << "bitmap [" << fn << "] is destroyed" << std::endl;
    if(fn.empty())std::cout << "bitmap destroyed" << std::endl;
    delete[] pixels;
}
int Bitmap::getUV(float u,float v){
    int tx = int(u*w);
    int ty = int(v*h);
    tx%=w;
    ty%=h;
    return pixels[tx+ty*w];
}