#include "sphere.h"

#include"mat.h"
#include"vec3.h"
#include"vec4.h"

CSphere::CSphere()
{
};

CSphere::~CSphere()
{
};
///////////////////////////////////////////////////////////////////////////////
//
void CSphere::create(int n)
{
    clear();
    float s, c;
       
    for(int i=0; i<n; i++)
    {
        oposition.push_back(0);
        oposition.push_back(1.0f);
        oposition.push_back(0);
        otexture.push_back(0.5);
        otexture.push_back(0.5);
 
        s = sin(i/(float)n*2.0*M_PI);
        c = cos(i/(float)n*2.0*M_PI);
        oposition.push_back(s);
        oposition.push_back(-1.0f);
        oposition.push_back(c);
        otexture.push_back((1.0f+s)*0.5f);
        otexture.push_back((1.0f+c)*0.5f);

        s = sin((i+1)/(float)n*2.0*M_PI);
        c = cos((i+1)/(float)n*2.0*M_PI);
        oposition.push_back(s);
        oposition.push_back(-1.0f);
        oposition.push_back(c);
        otexture.push_back((1.0f+s)*0.5f);
        otexture.push_back((1.0f+c)*0.5f);
    }
    for(int i=0;i<n;i++)
    {
        otriangleIndex.push_back(i*3);
        otriangleIndex.push_back(i*3+1);
        otriangleIndex.push_back(i*3+2);
    }
}