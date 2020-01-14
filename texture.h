#ifndef TEXTURE_H
#define TEXTURE_H

#include<fstream>
#include<string>
#include<GL/glew.h>

class CTexture
{
public:
    CTexture();
    CTexture(const std::string& fileName);
    void read(const std::string& fileName);
    void bind(unsigned int unit);
    static void Unbind();

    virtual ~CTexture();
    GLfloat color[3];
protected:
private:
    CTexture(const CTexture& other){}
    void operator=(const CTexture& other){}

    GLuint m_texture;
};

#endif //TEXTURE_H