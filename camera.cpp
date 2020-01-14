#include"camera.h"
CCamera::CCamera(const CVec3& pos)
{
    h_position=pos;
    pan = tilt =0.0f;
}

CMat CCamera::matrix()
{
    m =         CMat::rotX(tilt)
              * CMat::rotY(pan)
              * CMat::trans(-h_position);
    return m;
}
void CCamera::forward(float d)
{
    h_position.x+=sin(-pan)*d;
    h_position.z+=cos(pan)*d;
}
void CCamera::leftright(float d)
{
    h_position.x+=cos(-pan)*d;
    h_position.z+=sin(pan)*d;
}