#ifndef OBJECT_H
#define OBJECT_H

#include"mat.h"
#include"shader.h"
#include"texture.h"

class CObject
{
public:
    CObject();
    virtual int read(const std::string& fileName){return 0;};
    virtual void uploadPosTexNormIndex(){};
    virtual void drawFaces(int first=0,int last=0){};
    virtual void clear(){};
    virtual void calcNormals(){};
    virtual void create(int n){};
    virtual void create2(int,int,float,float){};
    virtual ~CObject(){};
};
#endif