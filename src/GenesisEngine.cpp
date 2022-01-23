#include <SDL2/SDL.h>
#include "Genesis/GenesisEngine.h"
GenesisEngine::GenesisEngine(int w,int h,int scale){
    WIDTH = w;
    HEIGHT = h;
    SCALE = scale;

    window = SDL_CreateWindow(
        "GenesisEngine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH*SCALE,HEIGHT*SCALE,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,HEIGHT
    );
}

GenesisEngine::~GenesisEngine(){
    
}

void GenesisEngine::init(){
}

void GenesisEngine::tick(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
            running=false;
            break;
        }
    }
}

void GenesisEngine::updatePixels(Uint32* pixels,int pitch){
    SDL_UpdateTexture(texture,nullptr,pixels,pitch);
}

void GenesisEngine::render(){
    SDL_RenderCopy(renderer,texture,nullptr,nullptr);
    SDL_RenderPresent(renderer);
}

bool GenesisEngine::isRunning(){
    return running;
}

void GenesisEngine::DestroyEverything(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}