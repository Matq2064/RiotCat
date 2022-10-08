#ifndef RIOTCATE_RECT_H
#define RIOTCATE_RECT_H

#include <SDL.h>

class CHandleRect {
protected:
    double m_x, m_y, m_w, m_h;

public:
    CHandleRect();
    CHandleRect(double x, double y, double w, double h);

    SDL_Rect GetRect();
};

#endif //RIOTCATE_RECT_H
