#ifndef RIOTCAT_DRAWING_H
#define RIOTCAT_DRAWING_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
using namespace std;

class CDrawing
{
private:
    SDL_Renderer* m_pRenderer = nullptr;

public:
    CDrawing(SDL_Renderer* pRenderer);
    ~CDrawing();

    void Clear();
    void Present();
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetColor(SDL_Color color);
    void FillRect(SDL_Rect* pRect);
    SDL_Renderer* Renderer() const { return m_pRenderer; }
};

#endif //RIOTCAT_DRAWING_H
