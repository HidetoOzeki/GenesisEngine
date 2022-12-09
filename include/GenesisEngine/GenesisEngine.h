#ifndef GENESIS_ENGINE_H
#define GENESIS_ENGINE_H

#include "SDL2/SDL.h"

class GenesisEngine{

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    public:

    int RENDERER_WIDTH = 0;
    int RENDERER_HEIGHT = 0;
    int WINDOW_SCALE = 1;

    ~GenesisEngine();
    GenesisEngine(const char* title,int WIDTH,int HEIGHT,int SCALE);

    void setVideoBuffer(Uint32* pixels);
    void saveVideoBuffer();
    void saveVideoBuffer(const char* filename);
    void Destroy();


};

#endif