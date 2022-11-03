#ifndef RIOTCAT_DRAWING_H
#define RIOTCAT_DRAWING_H

#include "Camera.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <iostream>
using namespace std;

class CDrawing
{
private:
    SDL_Renderer* m_pRenderer = nullptr;
    CCamera* m_pCamera = nullptr;
    map<const char*, SDL_Surface*> m_aSurfaces;
    map<const char*, SDL_Texture*> m_aTextures;

public:
    CDrawing(SDL_Renderer* pRenderer);
    ~CDrawing();

    SDL_Surface* LoadSurface(const char* filepath, const char* key);
    SDL_Surface* GetSurface(const char* key);
    SDL_Texture* TextureFromSurface(const char* surface_key, const char* key);
    SDL_Texture* GetTexture(const char* key);
    void Clear();
    void Present();
    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetColor(SDL_Color color);
    void RenderCopy(SDL_Texture* pTexture, SDL_Rect* srcrect, SDL_Rect* dstrect, bool translate);
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
