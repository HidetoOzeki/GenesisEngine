#ifndef SCREEN_3D_H
#define SCREEN_3D_H
#include <SDL2/SDL.h>
#include "Math.h"
#include "Bitmap.h"
#include <iostream>

struct VertexBufferObject {

    VertexBufferObject(){
        int length = 0;
    }

    ~VertexBufferObject(){ 
        delete[] VertexBuffer;
        delete[] Color;
        delete[] UVcoord;
        delete[] normal;
    }
    int length;
    float* VertexBuffer;
    float* Color;
    float* UVcoord;
    float* normal;
};

class Screen3D{

    private:
    int width;
    int height;
    Uint32* framebuffer;
    float* zbuffer;
    Bitmap* texture;


    public:
    Screen3D(int w,int h,Uint32* fb);
    ~Screen3D(){
        delete[] framebuffer;
        delete[] zbuffer;
        if(texture)delete texture;
        std::cout << "Screen3d Destructor Called" << std::endl;
    }

    void clear(int col);

    void put(int x,int y,int col);

    VertexBufferObject CreateVBO(int length);

    void Triangle(Vector3 v1,Vector3 v2,Vector3 v3);
};

#endif