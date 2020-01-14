#include"mat.h"
#include"quaternion.h"
#include"vec3.h"
#include"vec4.h"


CMat::CMat()
{
};
CMat::~CMat()
{
}

void CMat::disp()
{
    for(int i=0;i<16;i++)
    {
        printf("%f ",d[i]);
        if((i%4)==3)printf("\n");
    };
    printf("\n");
}
CMat CMat::one()
{
    CMat out;
    out[ 0]=1.0f;   out[ 1]=0.0f;   out[ 2]=0.0f;   out[ 3]=0.0f;
    out[ 4]=0.0f;   out[ 5]=1.0f;   out[ 6]=0.0f;   out[ 7]=0.0f;
    out[ 8]=0.0f;   out[ 9]=0.0f;   out[10]=1.0f;   out[11]=0.0f;
    out[12]=0.0f;   out[13]=0.0f;   out[14]=0.0f;   out[15]=1.0f;
    return out;
}
CMat CMat::perspective(float fov, float aspect, float near, float far)
{
    CMat out;
    float tfov=tan(fov/2.0);
    out[ 0]=1.0f/(aspect*tfov); out[ 1]=0.0f;         out[ 2]=0.0f;                       out[ 3]= 0.0f;
    out[ 4]=0.0f;               out[ 5] = 1.0f/tfov;  out[ 6]=0.0f;                       out[ 7]= 0.0f;
    out[ 8]=0.0f;               out[ 9]=0.0f;         out[10]=-(far+near)/(far-near);     out[11]=-1.0f;
    out[12]=0.0f;               out[13]=0.0f;         out[14]=-2.0f*far*near/(far -near); out[15]= 0.0f;
    return out;
}
CMat CMat::trans(float x,float y,float z)
{
    CMat out;
    out[ 0]=1.0f;   out[ 1]=0.0f;   out[ 2]=0.0f;   out[ 3]=0.0f;
    out[ 4]=0.0f;   out[ 5]=1.0f;   out[ 6]=0.0f;   out[ 7]=0.0f;
    out[ 8]=0.0f;   out[ 9]=0.0f;   out[10]=1.0f;   out[11]=0.0f;
    out[12]=x;      out[13]=y;      out[14]=z;      out[15]=1.0f;
    return out;
}
CMat CMat::trans(const CVec3& pos)
{
    return trans(pos.x,pos.y,pos.z);
};
CMat CMat::rotX(float a)
{
    CMat out;
    float s=sinf(a);
    float c=cosf(a);
    out[ 0]=1.0f;   out[ 1]=0.0f;   out[ 2]=0.0f;   out[ 3]=0.0f;
    out[ 4]=0.0f;   out[ 5]=c;      out[ 6]=-s;     out[ 7]=0.0f;
    out[ 8]=0.0f;   out[ 9]=s;      out[10]= c;     out[11]=0.0f;
    out[12]=0.0f;   out[13]=0.0f;   out[14]=0.0f;   out[15]=1.0f;
    return out;
}
CMat CMat::rotY(float a)
{
    CMat out;
    float s=sinf(a);
    float c=cosf(a);
    out[ 0]=c   ;   out[ 1]=0.0f;   out[ 2]=-s;     out[ 3]=0.0f;
    out[ 4]=0.0f;   out[ 5]=1.0f;   out[ 6]=0.0f;   out[ 7]=0.0f;
    out[ 8]=s   ;   out[ 9]=0.0f;   out[10]= c;     out[11]=0.0f;
    out[12]=0.0f;   out[13]=0.0f;   out[14]=0.0f;   out[15]=1.0f;
    return out;   
}
CMat CMat::rotZ(float a)
{
    CMat out;
    float s=sinf(a);
    float c=cosf(a);
    out[ 0]=c;      out[ 1]=-s;     out[ 2]=0.0f;   out[ 3]=0.0f;
    out[ 4]=s;      out[ 5]=c;      out[ 6]=0.0f;   out[ 7]=0.0f;
    out[ 8]=0.0f;   out[ 9]=0.0f;   out[10]=1.0f;   out[11]=0.0f;
    out[12]=0.0f;   out[13]=0.0f;   out[14]=0.0f;   out[15]=1.0f;
    return out;
}
CMat CMat::lookAt(const CVec3 &eye, const CVec3 &at, const CVec3 &up)
{
    CMat o;
    CVec3 X,Y,Z;
    Z = (eye - at).normalize();
    Y = up;
    X = Y.cross(Z).normalize();
    Y = Z.cross(X).normalize();
    o[ 0]=X[0];o[ 1]=Y[0];o[ 2]=Z[0];o[ 3]=0.0f;
    o[ 4]=X[1];o[ 5]=Y[1];o[ 6]=Z[1];o[ 7]=0.0f;
    o[ 8]=X[2];o[ 9]=Y[2];o[10]=Z[2];o[11]=0.0f;
    o[12]=-X.dot(eye);o[13]=-Y.dot(eye);o[14]=-Z.dot(eye);o[15]=1.0f;
    return o;
} 
CMat CMat::operator*(float in)
{
    CMat o;
    for(int i=0;i<16;i++)o[i]=d[i]*in;
    return o;
}
CMat CMat::operator*(CMat i)
{
    CMat o;

    o[ 0]=d[ 0]*i[ 0] + d[ 4]*i[ 1] + d[ 8]*i[ 2] + d[12]*i[ 3];
    o[ 1]=d[ 1]*i[ 0] + d[ 5]*i[ 1] + d[ 9]*i[ 2] + d[13]*i[ 3];
    o[ 2]=d[ 2]*i[ 0] + d[ 6]*i[ 1] + d[10]*i[ 2] + d[14]*i[ 3];
    o[ 3]=d[ 3]*i[ 0] + d[ 7]*i[ 1] + d[11]*i[ 2] + d[15]*i[ 3];    
    o[ 4]=d[ 0]*i[ 4] + d[ 4]*i[ 5] + d[ 8]*i[ 6] + d[12]*i[ 7];
    o[ 5]=d[ 1]*i[ 4] + d[ 5]*i[ 5] + d[ 9]*i[ 6] + d[13]*i[ 7];
    o[ 6]=d[ 2]*i[ 4] + d[ 6]*i[ 5] + d[10]*i[ 6] + d[14]*i[ 7];    
    o[ 7]=d[ 3]*i[ 4] + d[ 7]*i[ 5] + d[11]*i[ 6] + d[15]*i[ 7];
    o[ 8]=d[ 0]*i[ 8] + d[ 4]*i[ 9] + d[ 8]*i[10] + d[12]*i[11];
    o[ 9]=d[ 1]*i[ 8] + d[ 5]*i[ 9] + d[ 9]*i[10] + d[13]*i[11];    
    o[10]=d[ 2]*i[ 8] + d[ 6]*i[ 9] + d[10]*i[10] + d[14]*i[11];
    o[11]=d[ 3]*i[ 8] + d[ 7]*i[ 9] + d[11]*i[10] + d[15]*i[11];
    o[12]=d[ 0]*i[12] + d[ 4]*i[13] + d[ 8]*i[14] + d[12]*i[15];
    o[13]=d[ 1]*i[12] + d[ 5]*i[13] + d[ 9]*i[14] + d[13]*i[15];
    o[14]=d[ 2]*i[12] + d[ 6]*i[13] + d[10]*i[14] + d[14]*i[15];
    o[15]=d[ 3]*i[12] + d[ 7]*i[13] + d[11]*i[14] + d[15]*i[15];

    return o;
}
CMat CMat::operator=(CQuaternion q)
{
    CMat o;
    //row 1
    o[0]=1-2*q.j*q.j - 2*q.k*q.k;
    o[1]=  2*q.i*q.j - 2*q.k*q.w;
    o[2]=  2*q.i*q.k + 2*q.j*q.w;
    o[3]=0.0f;
    //row 2
    o[4]=  2*q.i*q.j + 2*q.k*q.w;
    o[5]=1-2*q.i*q.i - 2*q.k*q.k;
    o[6]=  2*q.j*q.k - 2*q.i*q.w;
    o[7]=0.0f;
    //row 3

    return o;
};
