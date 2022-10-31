#ifndef RIOTCAT_CAMERA_H
#define RIOTCAT_CAMERA_H

#include "Rect.h"

enum FollowMode {
    FOLLOW_INSTANT,
    FOLLOW_SLOW
};

class CCamera : public CHandleRect {
private:
    CHandleRect* m_pFollow = nullptr;
    FollowMode m_Mode;

public:
    CCamera(double startx, double starty, double width, double height, FollowMode mode = FOLLOW_INSTANT);

    void Tick();
    void Translate(int *x, int *y);
    void Translate(double *x, double *y);
    void ReverseTranslate(int* outx, int* outy);
    void ReverseTranslate(double* outx, double* outy);
    void SetFollow(CHandleRect* pFollow);
};

#endif //RIOTCAT_CAMERA_H
