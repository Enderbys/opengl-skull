#ifndef DISK_H
#define DISK_H
#include<GL/glew.h>
#include<vector>
#include<iostream>
#include<math.h>
#include"meshPTNI.h"

class CVec3;
class CVec4;
class CMat;

class CDisk : public CMeshPTNI
{
public:
    CDisk();
    ~CDisk();
    void create(int n,float sz);
};
#endif