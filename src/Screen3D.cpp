#include "GenesisEngine/gfx/Screen3D.h"

Screen3D::Screen3D(int w,int h,Uint32* fb){
    framebuffer = fb;
    width = w;
    height = h;
}

void Screen3D::clear(int col){
    for(int i = 0;i < width*height;i++){
        framebuffer[i] = col;
    }
}

void Screen3D::put(int x,int y,int col){
    if((x<0||x>=width)||(y<0||y>=height))return;
    framebuffer[x+y*width] = col;
}

VertexBufferObject Screen3D::CreateVBO(int length){
    VertexBufferObject vbo;
    return vbo;
}

void Screen3D::Triangle(Vector3 v1,Vector3 v2,Vector3 v3){

}