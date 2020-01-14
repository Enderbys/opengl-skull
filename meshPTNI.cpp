#include "meshPTNI.h"

#include"mat.h"
#include"vec3.h"
#include"vec4.h"

CMeshPTNI::CMeshPTNI()
{
    m_faceVAO = 0;
    for(int i=0;i<NUM_BUFFERS_VB;i++)
        m_faceBuffers[i]=0;
//    visible=true;
};

CMeshPTNI::~CMeshPTNI()
{
    if(m_faceVAO)
        glDeleteVertexArrays(1, &m_faceVAO);
};
///////////////////////////////////////////////////////////////////////////////
//
void CMeshPTNI::uploadPosTexNormIndex()//genFacesAndUpload()
{
    //One
    //Create VAO with 4 buffers
    // 0-position       3 floats/position
    // 1=texture coords 2 floats/position
    // 2=normals        3 floats/position
    // 3=indexes        3 unsigned ints, vertexIndex,textureIndex, normalIndex

    glGenVertexArrays(1, &m_faceVAO); //create 1 VAO
    glBindVertexArray(m_faceVAO);     //bind the new VAO
    glGenBuffers(NUM_BUFFERS_VB,m_faceBuffers);  //create 4 buffers
                                                 //as NUM_BUFFERS=4
                                                 //POSITION_VB=0
                                                 //TEXCOORD_VB=1
                                                 //NORMAL_VB  =2
                                                 //INDEX_VB   =3
    //Two
    //Bind the new position buffer
    glBindBuffer(   GL_ARRAY_BUFFER,
                    m_faceBuffers[POSITION_VB]); // 0
    //Upload the position data
    glBufferData(   GL_ARRAY_BUFFER,
                    oposition.size() * sizeof(float),
                    &oposition.front(),
                    GL_STATIC_DRAW);
    //Enable and define the position buffer (3 floats/vertex)
    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //--------------------------------------------------------------
    //Three
    //Bind the new texture buffer
    glBindBuffer(   GL_ARRAY_BUFFER,
                    m_faceBuffers[TEXCOORD_VB]); // 1
    //Upload the texture data
    glBufferData(   GL_ARRAY_BUFFER,
                    otexture.size() * sizeof(float),
                    &otexture.front(),
                    GL_STATIC_DRAW);
    //Enable and define the texture buffer (2 floats/vertex)
    glEnableVertexAttribArray(TEXCOORD_VB);
    glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);
    //--------------------------------------------------------------
    //Four
    //Bind the new normal buffer
    glBindBuffer(   GL_ARRAY_BUFFER,
                    m_faceBuffers[NORMAL_VB]); // 2
    //Upload the normal data
    glBufferData(   GL_ARRAY_BUFFER,
                    onormal.size() * sizeof(GLfloat),
                    &onormal.front(),
                    GL_STATIC_DRAW);
    //Enable and define the normal buffer (3 floats/vertex)
    glEnableVertexAttribArray(NORMAL_VB);
    glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //------------------------------------------------------------
    //Five
    //Bind the new index buffer, note it's an element array buffer
    glBindBuffer(   GL_ELEMENT_ARRAY_BUFFER,
                    m_faceBuffers[INDEX_VB]);
    //Upload the index data
    glBufferData(   GL_ELEMENT_ARRAY_BUFFER,
                    otriangleIndex.size() * sizeof(unsigned int),
                    &otriangleIndex.front(),
                    GL_STATIC_DRAW);
    //------------------------------------------------------------
    glBindVertexArray(0);
    m_faceTriangles=otriangleIndex.size()/3;
}
///////////////////////////////////////////////////////////////////////////////
//

void CMeshPTNI::info()
{
    std::cout << "oposition=" << oposition.size() << std::endl;
    std::cout << "onormal=" << onormal.size() << std::endl;
    std::cout << "otexture=" << otexture.size() << std::endl;
    std::cout << "otriangleIndex=" << otriangleIndex.size() << std::endl;
}
///////////////////////////////////////////////////////////////////////////////
//
void CMeshPTNI::maxmin(CVec3 &max, CVec3 &min)
{
    float x,y,z;
    x=oposition[0];
    y=oposition[1];
    z=oposition[2];
    max.x=min.x=x;
    max.y=min.y=y;
    max.z=min.z=z;
    for(unsigned int i = 0; i<oposition.size();i+=3)
    {
        x=oposition[i  ];
        y=oposition[i+1];
        z=oposition[i+2];
        if(x>max.x)max.x=x;
        if(x<min.x)min.x=x;
        if(y>max.y)max.y=y;
        if(y<min.y)min.y=y;
        if(z>max.z)max.z=z;
        if(z<min.z)min.z=z;
    }   
}
///////////////////////////////////////////////////////////////////////////////
//
void CMeshPTNI::normalizeSize()
{
    float x,y,z,w,max=0;
    for(unsigned int i = 0; i<oposition.size();i+=3)
    {
        x=oposition[i  ];
        y=oposition[i+1];
        z=oposition[i+2];
        w=x*x+y*y+z*z;
        if(w>max)max=w;
    }
    w=1/sqrt(max);
    for(unsigned int i = 0; i<oposition.size();i++)
        oposition[i]*=w;  
}
///////////////////////////////////////////////////////////////////////////////
void CMeshPTNI::scale(float s)
{
    for(unsigned int i = 0; i<oposition.size();i++)
    {
        oposition[i  ]*=s;
    }
}
void CMeshPTNI::displace(float x,float y,float z)
{
    for(unsigned int i = 0; i<oposition.size();i+=3)
    {
        oposition[i  ]+=x;
        oposition[i+1]+=y;
        oposition[i+2]+=z;
    }
}
/////////////////////////////////////////////////////////////////////////////////
void CMeshPTNI::calcNormals()
{
    onormal.clear();
    CVec3 a,b,c,n;
    for(unsigned int i=0;i<otriangleIndex.size();i+=3)
    {
        a=CVec3(oposition[i*3  ],oposition[i*3+1],oposition[i*3+2]);
        b=CVec3(oposition[i*3+3],oposition[i*3+4],oposition[i*3+5]);
        c=CVec3(oposition[i*3+6],oposition[i*3+7],oposition[i*3+8]);

        CVec3 n=((a-b).cross(a-c)).normalize();
        for(int j=0;j<3;j++)
        {
            onormal.push_back(n[0]);
            onormal.push_back(n[1]);
            onormal.push_back(n[2]);
        }
    }
};

void CMeshPTNI::drawFaces(int first,int last)
{
//    if(!visible)return;
    CObject::drawFaces(first,last);
    if((first==0)&&(last==0))last=m_faceTriangles;
    else
    {
        while(first<0)first+=m_faceTriangles;
        while(last<0)last+=m_faceTriangles;
        first=first%m_faceTriangles;
        last=last%m_faceTriangles;
    }
    glBindVertexArray(m_faceVAO);
    glDrawElements(GL_TRIANGLES, last*3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
///////////////////////////////////////////////////////////////////////////////
void CMeshPTNI::calcNormalLines(float sz)
{
    onormalLines.clear();
    onormalIndex.clear();
    CVec3 a,n;
    for(unsigned int i=0;i<otriangleIndex.size();i++)
    {
        a=CVec3(oposition[i*3  ],oposition[i*3+1],oposition[i*3+2]);
        n=CVec3(onormal[i*3  ],onormal[i*3+1],onormal[i*3+2]);
        onormalLines.push_back(a[0]);
        onormalLines.push_back(a[1]);
        onormalLines.push_back(a[2]);
        onormalLines.push_back(a[0]+n[0]*sz);
        onormalLines.push_back(a[1]+n[1]*sz);
        onormalLines.push_back(a[2]+n[2]*sz);
    }
    for(unsigned int i=0;i<onormalLines.size()/3;i++)
        onormalIndex.push_back(i);
}
void CMeshPTNI::genNormalLinesAndUpload()
{
//One
    glGenVertexArrays(1,&m_normalVAO);
    glBindVertexArray(m_normalVAO);
    glGenBuffers(NUM_BUFFERS_NORM_VB,m_normalBuffers);
//Two
    glBindBuffer(GL_ARRAY_BUFFER,
        m_normalBuffers[POSITION_NORM_VB]);
    //
    glBufferData(GL_ARRAY_BUFFER,
        onormalLines.size() * sizeof(float), &onormalLines.front(),
        GL_STATIC_DRAW);
    //
    glEnableVertexAttribArray(POSITION_NORM_VB);
    glVertexAttribPointer(POSITION_NORM_VB, 3,GL_FLOAT,GL_FALSE, 0, 0);
    //
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_normalBuffers[INDEX_NORM_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        onormalIndex.size() * sizeof(unsigned int),
        &onormalIndex.front(), GL_STATIC_DRAW);
    glBindVertexArray(0);
    m_normalLines=onormalIndex.size()/2;
    printf("%d\n",m_normalLines);
};

void CMeshPTNI::drawNormals()
{
//    if(!visible)return;
    glBindVertexArray(m_normalVAO);
    glDrawElements(GL_LINES, m_normalLines*2, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
};
///////////////////////////////////////////////////////////////////////////////
//

void CMeshPTNI::clear()
{
    oposition.clear();
    onormal.clear();
    otexture.clear();
    otriangleIndex.clear();
}
