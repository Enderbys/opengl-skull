#include"quaternion.h"

CQuaternion::CQuaternion()
{
};

CQuaternion::~CQuaternion()
{
};
CQuaternion::CQuaternion(float i,float j,float k,float w)
{
    this->i=i;this->j=j;this->k=k;
    this->w=w;
    normalize();
};
CQuaternion::CQuaternion(const CVec3& v,float a)
{
    float S = sin(a/2.0f);
    CVec3 v1=v.normalize();
    i=S*v1.x;
    j=S*v1.y;
    k=S*v1.z;
    r= cosf(a/2.0f);
};
CQuaternion CQuaternion::normalize()
{
    float d=sqrt(i*i+j*j+k*k);
    return CQuaternion(i/d,j/d,k/d,w);
}

CMat CQuaternion::matrix()
{
    CMat out;

    out[0]=1-2*j*j-2*k*k; out[1]=  2*i*j+2*k*w;  out[2]=  2*i*k-2*j*w;  out[3]=0.0f;
    out[4]=2*i*j-2*k*w;   out[5]=1-2*i*i-2*k*k;  out[6]=  2*j*k+2*i*w;  out[7]=0.0f;
    out[8]=2*i*k+2*j*w;   out[9]=  2*j*k-2*i*w; out[10]=1-2*i*i-2*j*j; out[11]=0.0f;
    out[12]=out[13]=out[14]=0.0f;out[15]=1.0f;
    return out;
}
