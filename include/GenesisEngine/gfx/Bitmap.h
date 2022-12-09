#ifndef BITMAP_H
#define BITMAP_H
#include <string>
class Bitmap{
    public:
    int* pixels;
    std::string fn;
    int w,h;
    Bitmap(const char*);
    ~Bitmap();
    int getUV(float u,float v);
    int getWidth();
    void destroy();
};
#endif