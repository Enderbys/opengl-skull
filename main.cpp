#include<map>
#include<iostream>
#include"display.h"
#include"shader.h"
#include"texture.h"
#include"camera.h"
#include"model.h"
#include"meshPTNI.h"
#include"cone.h"
#include"disk.h"
#include"terrain.h"
#include"mat.h"
#include"quaternion.h"
#include"object.h"
#include"objinst.h"
#include"functions.h"

#define WIDTH 800
#define HEIGHT 600

SDL_Event event;
float mouseX,mouseY;
std::map<unsigned int,bool>keys;
bool input()
{
    unsigned int k;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {  
        case SDL_QUIT:
            return false;
            break;            
        case SDL_MOUSEMOTION:
            mouseX=(2.0*(float)event.motion.x)/WIDTH-1.0f;
            mouseY=1.0f - (2.0*(float)event.motion.y)/HEIGHT;
            break;
        case SDL_KEYDOWN:
            k=event.key.keysym.sym;
            if(keys.find(k)==keys.end())
                keys.insert(std::make_pair(k,true));
            else
                keys[k]=true;
            break;
        case SDL_KEYUP:
            k=event.key.keysym.sym;
            keys[k]=false;
            break;
        }
    };
    return true;
}




const float deg =M_PI/180.0;
const float fovy=60.0f*deg;

int main()
{

    CDisplay display(WIDTH,HEIGHT, "Hello World");

    CShader  lxShader;
    GLuint geo = glCreateShader(GL_GEOMETRY_SHADER);
    printf("geo=%u\n",geo);

    lxShader.read("/home/hazel/c++/OpenGL/shaders/hShaders/h04");
    GLuint uObjectWorld      =lxShader.uniform("uObjectWorld");
    GLuint uWorldCamera      =lxShader.uniform("uWorldCamera");
    GLuint uCameraProjection =lxShader.uniform("uCameraProjection");
    GLuint uLightPos         =lxShader.uniform("uLightPos");
    GLuint uLightColor       =lxShader.uniform("uLightColor");
    GLuint uShini            =lxShader.uniform("uShini");
    GLuint uBoing            =lxShader.uniform("uBoing");
    CTexture whiteTexture;
    CTexture blotchyTexture;
    CTexture brickTexture;
    CTexture skullTexture;
    whiteTexture.read("/home/hazel/c++/OpenGL/textures/white.tga");
    blotchyTexture.read("/home/hazel/c++/OpenGL/textures/blotchy.tga");
    brickTexture.read("/home/hazel/c++/OpenGL/textures/bricks.jpg");
    skullTexture.read("/home/hazel/c++/OpenGL/textures/skull.jpg");

    CModel cube;
    cube.read("/home/hazel/c++/OpenGL/objects/cube.obj"); 
    cube.uploadPosTexNormIndex();
    cube.clear();

    CModel skull;
    skull.read("/home/hazel/c++/OpenGL/objects/skull.obj"); 
//    skull.normalizeSize();
//    skull.calcNormals();
    skull.uploadPosTexNormIndex();
    skull.clear();

    CCone cone;
    cone.create(16);
    cone.calcNormals();
    cone.uploadPosTexNormIndex();
    cone.clear();
  
    std::vector<CObjInst*>objs;

    objs.push_back(new CObjInst);
    objs[0]->uObjectWorld = uObjectWorld;
    objs[0]->pShader=&lxShader;
    objs[0]->pObject = &skull;
    objs[0]->pTexture = &skullTexture;
    objs[0]->pParent = NULL;
    objs[0]->worldMatrix = CMat::trans(0,-8,0);
    objs[0]->axis = CVec3(1,0,0).normalize();

    objs.push_back(new CObjInst);
    objs[1]->uObjectWorld = uObjectWorld;
    objs[1]->pShader=&lxShader;
    objs[1]->pObject = &cube;
    objs[1]->pTexture = &whiteTexture;
    objs[1]->pParent = NULL;
    objs[1]->worldMatrix = CMat::trans(32,0,0);
    objs[1]->axis = CVec3(0,1,0).normalize();

    float Shini=5.0;
    float boing;
    float lightAngle=0;
    float lightY=0;
    float lightR=30;
    bool wire=true;
    lxShader.bind();
    CMat mCameraProjection=CMat::perspective(60.0f*deg,800.0f/600.0f,0.1f,1000.0f);
    glUniformMatrix4fv(uCameraProjection,1,GL_FALSE,mCameraProjection.p());

    CCamera camera(CVec3(0,0,60));

    Uint32 dtic,tic=SDL_GetTicks()-1000.0f;
    float dt,timer=0;
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        dtic=SDL_GetTicks()-tic;
        tic=SDL_GetTicks();
        dt=float(dtic)/1000.0f;
        timer+=dt;
//        printf("%f, %f\n",1.0/dt,timer);

       
        if(!input())
        {
            display.Close();
        }
        float a=timer*deg;

        if(keys[SDLK_LSHIFT])
        {
            if(keys[SDLK_LEFT])lightAngle -=(180*deg*dt);
            if(keys[SDLK_RIGHT])lightAngle+=(180*deg*dt);
            if(keys[SDLK_UP])lightY+=10.0*dt;
            if(keys[SDLK_DOWN])lightY-=10.0*dt;
        }else if(keys[SDLK_LCTRL])
        {
            if(keys[SDLK_UP])lightR+=10*dt;
            if(keys[SDLK_DOWN])lightR-=10*dt;
        }else
        {
            if(keys[SDLK_w])
            {
                keys[SDLK_w]=false;
                wire=!wire;
            };
            if(keys[SDLK_LEFT])camera.pan-=(180*deg*dt);
            if(keys[SDLK_RIGHT])camera.pan+=(180*deg*dt);
            if(keys[SDLK_UP])camera.forward(-10.0*dt);
            if(keys[SDLK_DOWN])camera.forward(10.0*dt);
            if(keys[SDLK_PAGEUP])camera.leftright(-10.0*dt);
            if(keys[SDLK_PAGEDOWN])camera.leftright(10.0*dt);
            if(keys[SDLK_b])boing=0.01;
            Shini+=0.1*(keys[SDLK_q]-keys[SDLK_a]);
        }
        
        glPolygonMode( GL_FRONT_AND_BACK, wire?GL_LINE:GL_FILL );

        objs[1]->worldMatrix=CMat::trans(   lightR*sin(lightAngle),
                                            lightY,
                                            lightR*cos(lightAngle));
        glUniformMatrix4fv(uWorldCamera,1,GL_FALSE,camera.matrix().p());
        glUniform4f(uLightColor,sin(timer*0.8)*0.5+0.5,sin(timer*0.77)*0.5+0.5,sin(timer*0.76)*0.5+0.5,0);
        glUniform1f(uShini,Shini);
        if(boing>0.0)boing+=0.01;
        if(boing>5.0)boing=0.0;
        glUniform1f(uBoing,boing);
        objs[0]->angle=270*deg;
        for(int i=0;i<objs.size();i++)
        {
            if(i==0)
            {
                glUniform3f(uLightPos,lightR*sin(lightAngle),lightY,lightR*cos(lightAngle));
                glUniform1f(uBoing,boing);
                objs[i]->draw();
           }else
                glUniform3f(uLightPos,camera.h_position.x,camera.h_position.y,camera.h_position.z);

        }
        SDL_GL_SwapWindow(display.m_window);
    }
    return 0;
}
