#include "Camera.h"
#include <cmath>

CCamera::CCamera(double startx, double starty, double width, double height, FollowMode mode)
    : CHandleRect(startx, starty, width, height) {
    m_Mode = mode;
}

void CCamera::Tick() {
    if (m_pFollow) {
        double fX = m_pFollow->GetX();
        double fY = m_pFollow->GetY();
        double dX = fX - m_x;
        double dY = fY - m_y;

        double mX, mY;
        switch (m_Mode) {
            case FOLLOW_INSTANT: {
                mX = dX;
                mY = dY;
            } break;
            case FOLLOW_SLOW: {
                mX = dX * 0.01;
                mY = dY * 0.01;
            } break;
        }

        m_x += mX;
        m_y += mY;
    }
}

void CCamera::Translate(int* x, int* y) {
    *x -= (int)(m_x - m_w2);
    *y -= (int)(m_y - m_h2);
}

void CCamera::Translate(double* x, double* y) {
    *x -= m_x - m_w2;
    *y -= m_y - m_h2;
}

void CCamera::ReverseTranslate(int* outx, int* outy) {
    *outx += (int)(m_x - m_w2);
    *outy += (int)(m_y - m_h2);
}

void CCamera::ReverseTranslate(double* outx, double* outy) {
    *outx += m_x - m_w2;
    *outy += m_y - m_h2;
}

void CCamera::SetFollow(CHandleRect *pFollow) {
    m_pFollow = pFollow;
}
