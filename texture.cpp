#include"texture.h"
#include"stb_image.h"
#include<cassert>
#include<iostream>
CTexture::CTexture()
{
    m_texture=0;
}
CTexture::CTexture(const std::string& fileName)
{
    if(m_texture)
        glDeleteTextures(1, &m_texture);
    read(fileName);
}
void CTexture::read(const std::string& fileName)
{
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileName.c_str(),&width, &height, &numComponents, 4);
    if(imageData == NULL)
        std::cerr <<"Texture loading failed" << fileName << std::endl;
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //not glTextureParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // as in video

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    color[0]=(float)imageData[0]/255.0f;
    color[1]=(float)imageData[1]/255.0f;
    color[2]=(float)imageData[2]/255.0f;
    stbi_image_free(imageData);
}

CTexture::~CTexture()
{
    if(m_texture)
        glDeleteTextures(1, &m_texture);
}

void CTexture::bind(unsigned int unit)
{
    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
void CTexture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D,0);
}