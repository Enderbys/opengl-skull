#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<GL/glew.h>
#include"camera.h"

class CShader
{
public:
    CShader();
    CShader(const std::string& filename);
    void clear();
    void read(const std::string& filename);
    void bind();
    GLuint uniform(const char name[])
            {glGetUniformLocation(m_program,name);};
    virtual ~CShader();
protected:
private:
    static const unsigned int NUM_SHADERS = 3;
    CShader(const CShader& other){}
    void operator=(const CShader& other){}
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};

#endif //SHADER_H


