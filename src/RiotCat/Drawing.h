#ifndef RIOTCAT_DRAWING_H
#define RIOTCAT_DRAWING_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include "Camera.h"
using namespace std;

class CDrawing
{
private:
    SDL_Renderer* m_pRenderer = nullptr;
    CCamera* m_pCamera = nullptr;

public:
    CDrawing(SDL_Renderer* pRenderer);
    ~CDrawing();

    void Clear();
    void Present();
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetColor(SDL_Color color);
    void FillRect(SDL_Rect Rect, bool translate = false);
    void FillRect(int x, int y, int w, int h, bool translate = false);
    void FillRect(double x, double y, double w, double h, bool translate = false);
    void ReverseTranslate(int* outx, int* outy);
    void ReverseTranslate(double* outx, double* outy);
    void SetCamera(CCamera* pCamera);
    SDL_Renderer* Renderer() const { return m_pRenderer; }
    CCamera* Camera() const { return m_pCamera; }
};

#endif //RIOTCAT_DRAWING_H
