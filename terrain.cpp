#include "terrain.h"

#include"mat.h"
#include"vec3.h"
#include"vec4.h"

CTerrain::CTerrain()
{
};

CTerrain::~CTerrain()
{
};
///////////////////////////////////////////////////////////////////////////////
//

void CTerrain::create(int n,float sz)
{
    clear();   
    for(int i=0; i<n; i++)
    {
        float s = sz * sin(i/(float)n*2.0*M_PI);
        float c = sz * cos(i/(float)n*2.0*M_PI);
        oposition.push_back(s);
        oposition.push_back(-1.0f);
        oposition.push_back(c);
        otexture.push_back((1.0f+s)*0.5f);
        otexture.push_back((1.0f+c)*0.5f);
    }
    for(int i=0;i<n-2;i++)
    {
        otriangleIndex.push_back(0);
        otriangleIndex.push_back(i+1);
        otriangleIndex.push_back(i+2);
    }
}

void CTerrain::create2(int q,int tq,float min,float max)
{
    int steps=1<<q;
    int tsteps=1<<tq;
    int ix,iz;
    int index;
    float ftx,ftz;
    float fx,fz;
    int qa,qb,qc,qd;

    clear();
    for(iz=0;iz<=steps;iz++)
    {
        for(ix=0;ix<=steps;ix++)
        {
            ftx=ix/(float)steps;
            ftz=iz/(float)steps;
            fx=ftx*(max-min)+min;
            fz=ftz*(max-min)+min;
            index = ix+(steps+1)*iz;
            oposition.push_back(fx);
            oposition.push_back(-20.0f+40*(rand()/(float)RAND_MAX));     //dy
            oposition.push_back(fz);
            onormal.push_back(0);
            onormal.push_back(1);
            onormal.push_back(0);
            otexture.push_back(ftx*tsteps);
            otexture.push_back(ftz*tsteps);
         }
    }
    for(iz=0;iz<steps;iz++)
    {
        for(ix=0;ix<steps;ix++)
        {
            ftx=ix/(float)steps;
            ftz=iz/(float)steps;
            fx=ftx*(max-min)+min;
            fz=ftz*(max-min)+min;
            index = ix+(steps+1)*iz;
            qa=index;           qb=index+1;
            qc=index+steps+1;   qd=index+steps+2;
            otriangleIndex.push_back(qa);
            otriangleIndex.push_back(qd);
            otriangleIndex.push_back(qb);
            otriangleIndex.push_back(qa);
            otriangleIndex.push_back(qc);
            otriangleIndex.push_back(qd);
        }
    }
}
/*
void CTerrain::create2(int q,float min,float max)
{
    int steps=1<<q;
    int ix,iz;
    int index;
    float ftx,ftz;
    float fx,fz;
    int qa,qb,qc,qd;

    printf("q=%d\nsteps=%d\n",q,steps);

    printf("index\n");
    for(iz=0;iz<=steps;iz++)
    {
        for(ix=0;ix<=steps;ix++)
        {
            printf("[%2d]",ix+(steps+1)*iz);
        }
        printf("\n");
    }
    printf("text coords\n");
    for(iz=0;iz<=steps;iz++)
    {
        for(ix=0;ix<=steps;ix++)
        {
            ftx=ix/(float)steps;
            ftz=iz/(float)steps;
            printf("[%1.2f %1.2f]",ftx,ftz);
        }
        printf("\n");
    }
    printf("coords\n");
    for(iz=0;iz<=steps;iz++)
    {
        for(ix=0;ix<=steps;ix++)
        {
            ftx=ix/(float)steps;
            ftz=iz/(float)steps;
            fx=ftx*(max-min)+min;
            fz=ftz*(max-min)+min;
            index = ix+(steps+1)*iz;
            printf("[%1.2f %1.2f]",fx,fz);
        }
        printf("\n");
    }
    printf("quads\n");
    for(iz=0;iz<steps;iz++)
    {
        for(ix=0;ix<steps;ix++)
        {
            ftx=ix/(float)steps;
            ftz=iz/(float)steps;
            fx=ftx*(max-min)+min;
            fz=ftz*(max-min)+min;
            index = ix+(steps+1)*iz;
            qa=index;           qb=index+1;
            qc=index+steps+1;   qd=index+steps+2;
            printf("[%2d %2d %2d %2d]",qa,qb,qc,qd);
        }
        printf("\n");
    }
}
*/