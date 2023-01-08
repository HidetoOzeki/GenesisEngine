#ifndef GEN_MATH_H
#define GEN_MATH_H

#include <cmath>
#include <iostream>
#include <string>

template <typename T>
class Matrix{

    private:
    int row,col;
    T* m;

    public:

    Matrix(int r,int c){
        m = new T[r*c];
        row = r;
        col = c;
    }

    Matrix(int r,int c,T* matrix){
        row = r;
        col = c;
        m = new T[r*c];
        for(int i = 0;i < r*c;i++){
            at(i) = *(matrix+i);
        }
    }

    T& at(int index){
        return m[index];
    }

    T& at(int r,int c){
        return m[r*col+c];
    }

    const T& at(int r,int c) const {
        return m[r*col+c];
    }

    Matrix operator+(const Matrix& r){
        Matrix result(row,col);
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                result.at(i,j) = at(i,j)+r.at(i,j);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& r){
        Matrix result(row,col);
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                result.at(i,j) = at(i,j)-r.at(i,j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& r){
        Matrix result(row,col);

        return result;
    }

    void outElement(){
        std::string out = "";

        for(int i = -1;i < row+1;i++){
            bool separate_row = i==-1||i==row;
            for(int j = 0;j < col;j++){
                std::string str = separate_row ? "--" : std::to_string((int)at(i,j))+",";
                out+=str;
            }
            out+="\n";
        }

        std::cout << out << std::endl;

    }

};

typedef Matrix<double> Matrixd;
typedef Matrix<float> Matrixf;

class Vector2{

    float x,y;
    Vector2(){x=y=0.0;}

    void add(Vector2 v){ x+=v.x; y+=v.y;}

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
};

struct Vector3{

    Vector3(){x=y=z=0.0;}

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

struct Vector4{

    Vector4(){
        x=y=z=w=0.0;
    }

    void add(Vector4 v){
        x+=v.x;
        y+=v.y;
        z+=v.z;
        w+=v.w;
    }

    void sub(Vector4 v){
        x-=v.x;
        y-=v.y;
        z-=v.z;
        w-=v.w;
    }

    void mult(Vector4 v){
        x*=v.x;
        y*=v.y;
        z*=v.z;
        w*=v.w;
    }

    void div(Vector4 v){
        x/=v.x;
        y/=v.y;
        z/=v.z;
        w/=v.w;
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
    
    float x,y,z,w;
};


#endif