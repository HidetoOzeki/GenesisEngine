#include <SDL2/SDL.h>
#ifndef GENESIS_H
#define GENESIS_H

class GenesisEngine{
    private :
    int WIDTH = 320;
    int HEIGHT = 240;
    int SCALE = 3;
    bool running = true;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    
    public:

    GenesisEngine(int w,int h,int scale);
    ~GenesisEngine();

    void updatePixels(Uint32* pixels,int pitch);

    void init();
    void tick();
    void render();
    bool isRunning();
    void DestroyEverything();
};

#endif