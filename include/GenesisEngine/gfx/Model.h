#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Screen.h"
#include <string>

class Model {

    public:
    bool hasTexture = false;
    std::string oname = "";
    std::vector<Vec> vertices;
    std::vector<Face> faces;
    std::vector<UVcoordf> tex_coords;
    Model();
    Model(const char*);

    void fromText(const char*);
    void scale(float s);
};

#endif