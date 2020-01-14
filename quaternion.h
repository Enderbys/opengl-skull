#ifndef _QUATERNION
#define _QUATERNION
#include<stdio.h>
#include<math.h>
#include"mat.h"
#include"vec3.h"
#include"vec4.h"

class CQuaternion
{
public:
    CQuaternion();
    ~CQuaternion();
    CQuaternion(float x,float y,float z,float a);
    CQuaternion(const CVec3& v,float w);
    CQuaternion normalize();
    CMat matrix();
    union
    {
        struct{float x,y,z,w;};
        struct{float i,j,k,r;};
    };
private:
};
#endif