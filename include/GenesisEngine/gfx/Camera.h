#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"

class Camera{
    public:
    double FieldOfView;
    double perspective;
    Vector3 position;
    Vector3 angle; //roll pitch yaw
    Camera(){
        FieldOfView=90;
        //perspective = (width/2.0)/(tanf((FieldOfView/2.0)*3.14159265359/180.0));
        perspective = (tanf((FieldOfView/2.0)*3.14159265359/180.0));
    }

};
#endif