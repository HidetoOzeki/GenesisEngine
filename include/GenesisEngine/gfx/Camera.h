#ifndef CAMERA_H
#define CAMERA_H
#include "Screen.h"
#include "Model.h"

//static const Model cam_model = Model("res/camera.obj");
class Camera{
    
    Vec position;
    Vec angle;
    public:
    Camera(Vec p,Vec a);

    void addCameraToScene(Screen* screen);

    Vec getAngle(){
        return angle;
    }

    Vec getPosition(){
        return position;
    }

};
#endif