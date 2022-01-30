#include "Genesis/gfx/Bitmap.h"

Bitmap::Bitmap(){

}

Bitmap::Bitmap(const char* name){
image = SDL_LoadBMP(name);
if(image==NULL)std::cout << SDL_GetError() << " ::make sure libSDL2_image is linked" << std::endl;
if(image!=NULL)std::cout << "Bitmap successfuly loaded. (" << name << ")" << std::endl;
w = image->w;
h = image->h;
pixels = (Uint32*)image->pixels;
filename = name;
}

Bitmap::~Bitmap(){
	SDL_FreeSurface(image);
	std::cout << "Bitmap (" << filename << ") destructor called." << std::endl;
}

Uint32* Bitmap::getUV(float u,float v){
	return (Uint32*)pixels[(int)(u*w)+(int)(v*h)*w];
}