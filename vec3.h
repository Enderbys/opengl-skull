#ifndef _VEC3
#define _VEC3
#include<stdio.h>
#include<math.h>

class CVec4;
class CVec3
{
public:
    CVec3();
    ~CVec3();
    CVec3(float x,float y,float z);
    CVec3 normalize()const;
    CVec3 cross(CVec3 in);
    CVec3 cross(CVec3& a,CVec3& b);
    float dot(CVec3 in);
    void disp();
    CVec3 operator=(const CVec3& in);
    CVec3 operator=(const CVec4& in);
    float& operator[](int n){return m[n];};
    CVec3 operator*(int i) const {return CVec3(x*i,y*i,z*i);};
    CVec3 operator+(const CVec3& i)const;
    CVec3 operator+=(const CVec3& i);
    CVec3 operator-(const CVec3& i)const;

    CVec3 operator-()const;
    union
    {
    float m[3]{0,0,0};
    struct{float x,y,z;};
    struct{float i,j,k;};
    };
private:
};
#endif