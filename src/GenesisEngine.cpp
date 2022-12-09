#include <GenesisEngine/GenesisEngine.h>
#include <iostream>

GenesisEngine::GenesisEngine(const char* title,int WIDTH,int HEIGHT,int SCALE){
    GenesisEngine::RENDERER_WIDTH = WIDTH;
    GenesisEngine::RENDERER_HEIGHT = HEIGHT;
    GenesisEngine::WINDOW_SCALE = SCALE;

    std::cout << "GenesisEngine initialized" << std::endl;
    window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    RENDERER_WIDTH*WINDOW_SCALE,RENDERER_HEIGHT*WINDOW_SCALE,0);

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);
}

GenesisEngine::~GenesisEngine(){
    std::cout << "Engine destructor called" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

void GenesisEngine::Destroy(){
    std::cout << "Engine Destroy function called" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

void GenesisEngine::setVideoBuffer(Uint32* pixels){
    SDL_UpdateTexture(texture,nullptr,pixels,RENDERER_WIDTH*4);
    SDL_RenderCopy(renderer,texture,nullptr,nullptr);
    SDL_RenderPresent(renderer);
}

void GenesisEngine::saveVideoBuffer(const char* filename){
    SDL_Surface *sshot = SDL_GetWindowSurface(window);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, filename);
    SDL_FreeSurface(sshot);
    
}

void GenesisEngine::saveVideoBuffer(){
    saveVideoBuffer("screenshot.bmp");
}