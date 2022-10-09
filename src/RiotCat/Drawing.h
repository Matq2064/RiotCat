#ifndef RIOTCAT_DRAWING_H
#define RIOTCAT_DRAWING_H

#include <SDL.h>

class CDrawing
{
private:
    SDL_Renderer* m_pRenderer = nullptr;

public:
    CDrawing(SDL_Renderer* pRenderer);

    void Clear();
    void Present();
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void FillRect(SDL_Rect* pRect);
};

#endif //RIOTCAT_DRAWING_H
