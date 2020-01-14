#ifndef TERRAIN_H
#define TERRAIN_H
#include<GL/glew.h>
#include<vector>
#include<iostream>
#include<math.h>
#include"meshPTNI.h"

class CVec3;
class CVec4;
class CMat;

class CTerrain : public CMeshPTNI
{
public:
    CTerrain();
    ~CTerrain();
    void create(int n,float sz);
    void create2(int q,int tq,float min,float max);
    void create3(int q,int tq,float min,float max);
};
#endif