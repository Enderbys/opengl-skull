#include"display.h"

CDisplay::CDisplay(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);


    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4); //OpenGL 3+
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 2); //OpenGL 3.0

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width,height,SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();
    if(status != GLEW_OK)
    {
        std::cerr << "GLEW failed to initialize" << std::endl;
        
    }
    m_isClosed = false;
}

CDisplay::~CDisplay()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
void CDisplay::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}