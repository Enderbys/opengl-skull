#include "disk.h"

#include"mat.h"
#include"vec3.h"
#include"vec4.h"

CDisk::CDisk()
{
};

CDisk::~CDisk()
{
};
///////////////////////////////////////////////////////////////////////////////
//
void CDisk::create(int n,float sz)
{
    clear();   
    for(int i=0; i<n; i++)
    {
        float s = sz * sin(i/(float)n*2.0*M_PI);
        float c = sz * cos(i/(float)n*2.0*M_PI);
        oposition.push_back(s);
        oposition.push_back(-1.0f);
        oposition.push_back(c);
        otexture.push_back((1.0f+s)*0.5f);
        otexture.push_back((1.0f+c)*0.5f);
    }
    for(int i=0;i<n-2;i++)
    {
        otriangleIndex.push_back(0);
        otriangleIndex.push_back(i+1);
        otriangleIndex.push_back(i+2);
    }
}
