#ifndef SPHERE_H
#define SPHERE_H
#include<GL/glew.h>
#include<vector>
#include<iostream>
#include<math.h>
#include"meshPTNI.h"

class CVec3;
class CVec4;
class CMat;

class CSphere : public CMeshPTNI
{
public:
    CSphere();
    ~CSphere();
    void create(int n);
};
#endif