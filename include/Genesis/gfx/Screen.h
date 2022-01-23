#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

class Screen {
    private:

    int width,height;
    Uint32* pixels;

    public:

    Screen(int w,int h);
    void background(int color);
    Uint32* getRaster();
    int getWidth();
    int getHeight();
};

#endif