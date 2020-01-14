#include "vec3.h"
#include "vec4.h"
CVec3::CVec3()
{
    x=y=z=0.0f;
}

CVec3::~CVec3()
{
};

CVec3::CVec3(float x,float y,float z) 
{
    this->x=x;this->y=y;this->z=z;
};
CVec3 CVec3::normalize()const
{
    CVec3 out;
    float d=sqrt(x*x+y*y+z*z);
    out.x=x/d;
    out.y=y/d;
    out.z=z/d;
    return out;
}
CVec3 CVec3::operator=(const CVec3& in)
{
    x=in.x;
    y=in.y;
    z=in.z;
    return CVec3(x,y,z);
}
CVec3 CVec3::operator=(const CVec4& in)
{
    CVec3 out;
    if(in.w!=0.0)
    {
        out.x=x=in.x/in.w;
        out.y=y=in.y/in.w;
        out.z=z=in.z/in.w;
    }else
    {
        out.x=x=in.x;
        out.y=y=in.y;
        out.z=z=in.z;
    }
    return out;
}

CVec3 CVec3::cross(CVec3 in)
{
    CVec3 out;
    return CVec3(y*in.z - z*in.y,
                 z*in.x - x*in.z,
                 x*in.y - y*in.x);
};
CVec3 CVec3::cross(CVec3& a,CVec3& b)
{
    CVec3 out;
    x=a.y*b.z - a.z*b.y;
    y=a.z*b.x - a.x*b.z;
    z=a.x*b.y - a.y*b.x;
    return out;
};
float CVec3::dot(CVec3 in)
{
    return x*in.x + y*in.y + z*in.z;
};
CVec3 CVec3::operator+(const CVec3 &i)const
{
    return CVec3(x+i.x,y+i.y,z+i.z);
};
CVec3 CVec3::operator+=(const CVec3 &i)
{
    x+=i.x;y+=i.y;z+=i.z;
    printf("[%f %f %f]\n",i.x,i.y,i.z);
    return CVec3(x,y,z);
};
CVec3 CVec3::operator-(const CVec3 &i)const
{
    return CVec3(x-i.x,y-i.y,z-i.z);
};
CVec3 CVec3::operator-()const
{
    return CVec3(-x,-y,-z);
}
void CVec3::disp()
{
    printf("[%f %f %f]\n",x,y,z);
}