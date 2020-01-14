#ifndef MODEL_H
#define MODEL_H
#include<GL/glew.h>
#include<vector>
#include<iostream>
#include<math.h>
#include"meshPTNI.h"


class CVec3;
class CVec4;
class CMat;

class CModel: public CMeshPTNI
{
public:
    CModel();
    ~CModel();
    int read(const std::string& fileName);
    int write(const char *fName);
    void clear();
    void info();
protected:
private:
    int readNumber(FILE *f);
    std::vector<GLfloat>fposition;
    std::vector<GLfloat>ftexture;
    std::vector<GLfloat>fnormal;
};
#endif