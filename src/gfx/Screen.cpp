#include "Genesis/gfx/Screen.h"

Screen::Screen(int w,int h){
    width = w;
    height = h;
    pixels = new Uint32[width*height];
}

void Screen::background(int color){
    for(int i = 0;i < width*height;i++){
        pixels[i] = color;
    }
}

Uint32* Screen::getRaster(){
    return pixels;
}

int Screen::getWidth(){
    return width;
}

int Screen::getHeight(){
    return height;
}