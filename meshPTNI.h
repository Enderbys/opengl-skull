#ifndef MESH_H
#define MESH_H
#include<GL/glew.h>
#include<vector>
#include<iostream>
#include<math.h>
#include"object.h"

class CVec3;
class CVec4;
class CMat;

class CMeshPTNI : public CObject
{
public:
    CMeshPTNI();
    ~CMeshPTNI();
    void uploadPosTexNormIndex();
    void info();
    void normalizeSize();
    void maxmin(CVec3 &max,CVec3 &min);
    void scale(float s);
    void displace(float x,float y,float z);
    void calcNormals();
    void drawFaces(int first=0,int last=0);
    //
    void calcNormalLines(float sz);
    void genNormalLinesAndUpload();
    void drawNormals();    
    virtual void clear();
    virtual int read(const std::string& fileName){return 0;};
    virtual void create(int n){};
    virtual void create2(int,int,float,float){};

protected:
    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        INDEX_VB,
        NUM_BUFFERS_VB
    };
    enum
    {
        POSITION_NORM_VB,
        INDEX_NORM_VB,
        NUM_BUFFERS_NORM_VB
    };
    std::vector<GLfloat>oposition;
    std::vector<GLfloat>otexture;
    std::vector<GLfloat>onormal;
    std::vector<unsigned int>otriangleIndex;
private:

    //
    GLuint m_faceVAO; //vertex array object
    GLuint m_faceBuffers[NUM_BUFFERS_VB];
    unsigned int m_faceTriangles;

    std::vector<GLfloat>onormalLines;
    std::vector<unsigned int>onormalIndex;
    GLuint m_normalVAO;
    GLuint m_normalBuffers[NUM_BUFFERS_NORM_VB];
    unsigned int m_normalLines;
};
#endif