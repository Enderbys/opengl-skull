#ifndef _MAT
#define _MAT
#include<stdio.h>
#include<math.h>
class CVec3;
class CVec4;
class CQuaternion;

//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
//quaternion
// (a,b,c,d)*(e,f,g,h) =(ae-bf-cg-dh,
//                       be+af-dg+ch,
//                       ce+df+ag-bh,
//                       de-cf+bg+ah]


//////////////////////////////////////////////////////////////////////////
//
class CMat
{
public:
    CMat();
    CMat(   float a,float b,float c,float d,
            float e,float f,float g,float h,
            float i,float j,float k,float l,
            float m,float n,float o,float p)
        :d{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}{};
    ~CMat();
    void disp();
    static CMat one();
    float &operator[](int n){return d[n];};
    static CMat perspective(float fov, float aspect, float near, float far);
    static CMat trans(float x,float y,float z);
    static CMat trans(const CVec3& pos);
    static CMat rotX(float a);
    static CMat rotY(float a);
    static CMat rotZ(float a);
    static CMat lookAt(const CVec3 &eye, const CVec3 &at, const CVec3 &up);
    float *p(){return d;}; 
    CMat operator*(float i);
    CMat operator*(CMat i);
    CVec4 operator*(CVec4 &i);
    CMat operator=(CQuaternion q);
    float d[16]{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
protected:
private:
};
#endif
