#ifndef GEN_MATH_H
#define GEN_MATH_H

#include <cmath>

struct Vector2{

    Vector2(){
        x=y=0.0;
    }

    void add(Vector2 v){
        x+=v.x;
        y+=v.y;
    }

    void sub(Vector2 v){
        x-=v.x;
        y-=v.y;
    }

    void mult(Vector2 v){
        x*=v.x;
        y*=v.y;
    }

    void div(Vector2 v){
        x/=v.x;
        y/=v.y;
    }

    float magnitude(){
        return sqrt(x*x+y*y);
    }

    void normalize(){
        float mag = magnitude();
        x/=mag;
        y/=mag;
    }
    
    float x,y;
};

struct Vector3{

    Vector3(){
        x=y=z=0.0;
    }

    void add(Vector3 v){
        x+=v.x;
        y+=v.y;
        z+=v.z;
    }

    void sub(Vector3 v){
        x-=v.x;
        y-=v.y;
        z-=v.z;
    }

    void mult(Vector3 v){
        x*=v.x;
        y*=v.y;
        z*=v.z;
    }

    void div(Vector3 v){
        x/=v.x;
        y/=v.y;
        z/=v.z;
    }

    float magnitude(){
        return sqrt(x*x+y*y+z*z);
    }

    void normalize(){
        float mag = magnitude();
        x/=mag;
        y/=mag;
        z/=mag;
    }
    
    float x,y,z;
};

#endif