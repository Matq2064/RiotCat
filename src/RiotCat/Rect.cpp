#include "Rect.h"

CHandleRect::CHandleRect() {

}

CHandleRect::CHandleRect(double x, double y, double w, double h) {
    m_x = x;
    m_y = y;
    Morph(w, h);
}

SDL_Rect CHandleRect::GetRect() {
    SDL_Rect Rect;
    Rect.x = (int)(m_x - m_w/2);
    Rect.y = (int)(m_y - m_h/2);
    Rect.w = (int)(m_w);
    Rect.h = (int)(m_h);
    return Rect;
}

void CHandleRect::Morph(double w, double h) {
    m_w = w;
    m_h = h;
    m_w2 = w / 2.0;
    m_h2 = h / 2.0;
}