#ifndef RIOTCATE_RECT_H
#define RIOTCATE_RECT_H

#include <SDL.h>

class CHandleRect {
protected:
    double m_x, m_y, m_w, m_h, m_w2, m_h2;

public:
    CHandleRect();
    CHandleRect(double x, double y, double w, double h);

    SDL_Rect GetRect();
    void Morph(double w, double h);
};

#endif //RIOTCATE_RECT_H
