#ifndef CAMERA_H
#define CAMERA_H


#include "vec3.h"
#include "vec4.h"
#include "mat.h"

class CCamera
{
public:
    CCamera(const CVec3& pos);
    CMat matrix();
    void forward(float d);
    void leftright(float d);

    CMat m;
    CVec3 h_position;
    float pan,tilt;
    CMat *projectionMatrix;
protected:
private:
};
#endif //CAMERA_H
