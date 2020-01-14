#ifndef OBJINST_H
#define OBJINST_H
#include"functions.h"
#include"quaternion.h"
#include"mat.h"
#include"shader.h"
#include"texture.h"
#include"object.h"

class CObjInst
{
public:
    CObjInst();
    CMat getMatrix();
    void draw();
public:
    CObjInst *pParent;
    CObject  *pObject;
    CShader  *pShader;
    CTexture *pTexture;
//
    CMat      worldMatrix;
    bool      visible; 
    GLuint    uObjectWorld;
    CVec3     axis;
    float     angle;
//    
};

#endif
