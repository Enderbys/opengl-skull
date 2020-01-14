#ifndef CONE_H
#define CONE_H
#include<GL/glew.h>
#include<vector>
#include<iostream>
#include<math.h>
#include"meshPTNI.h"

class CVec3;
class CVec4;
class CMat;

class CCone : public CMeshPTNI
{
public:
    CCone();
    ~CCone();
    void create(int n);
};
#endif