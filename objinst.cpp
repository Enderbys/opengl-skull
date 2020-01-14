#include"objinst.h"
CObjInst::CObjInst()
{
    pParent      = NULL;
    pObject      = NULL;
    pShader      = NULL;
    pTexture     = NULL;

    worldMatrix  = CMat::one();
    visible      = true; 
    uObjectWorld = 0;
};
void CObjInst::draw()
{
    
    CMat temp;

    temp=getMatrix();

    glUniformMatrix4fv( uObjectWorld,1,
                        GL_FALSE,temp.p());
    if(pTexture) pTexture->bind(0);
    if(pShader)   pShader->bind();
    if(pObject)
    {
       pObject->drawFaces();
    }
}
CMat CObjInst::getMatrix()
{
    if(pParent)return pParent->getMatrix() * worldMatrix * CQuaternion(axis,angle).matrix();
    return worldMatrix * CQuaternion(axis,angle).matrix();
}