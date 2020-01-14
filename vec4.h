#ifndef _VEC4
#define _VEC4
#include<stdio.h>
#include<math.h>

class CVec3;
class CVec4
{
public:
    CVec4();
    ~CVec4();
    CVec4(float x,float y,float z,float w);
    CVec4 normalize();
    CVec4 operator=(const CVec3 &in);
    CVec4 operator=(const CVec4 &in);    
    union
    {
    float m[4]{0,0,0,0};
    struct{float x,y,z,w;};
    };
private:
};
#endif