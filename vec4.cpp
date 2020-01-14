#include"vec4.h"
#include"vec3.h"

CVec4::CVec4()
{
    x=y=z=w=0.0f;
}
CVec4::~CVec4()
{
};
CVec4::CVec4(float x,float y,float z,float w=0)
{
    this->x=x;this->y=y;this->z=z;this->w=w;
};
CVec4 CVec4::normalize()
{
    float d=sqrt(x*x+y*y+z*z+w*w);
    return CVec4(x/d,y/d,z/d,w/d);
};
CVec4 CVec4::operator=(const CVec3 &in)
{
    CVec4 out;
    out.x=x=in.x;
    out.y=y=in.y;
    out.z=z=in.z;
    out.w=w=0.0f;
    return out;
}
CVec4 CVec4::operator=(const CVec4 &in)
{
    CVec4 out;
    out.x=x=in.x;
    out.y=y=in.y;
    out.z=z=in.z;
    out.w=w=in.w;
    return out;
}