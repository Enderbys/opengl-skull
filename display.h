#ifndef DISPLAY_H
#define DISPLAY_H
#include<iostream>
#include <string>

#include<GL/glew.h>
#include <SDL2/SDL.h>


class CDisplay
{
public:
    CDisplay(int width, int height, const std::string& title);
    void Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
//    void Update();
    void Close(){m_isClosed=true;};
    bool IsClosed(){return m_isClosed;};
    SDL_Window* m_window;
    virtual ~CDisplay();
protected:
private:
    CDisplay(const CDisplay& other){}
    void operator=(const CDisplay& other){}


    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif //DISPLAY_H
