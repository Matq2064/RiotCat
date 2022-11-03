#include "Drawing.h"

CDrawing::CDrawing(SDL_Renderer* pRenderer) {
    m_pRenderer = pRenderer;

    LoadSurface("assets/test.png", "test");
    LoadSurface("assets/test2.png", "test2");
    LoadSurface("assets/test3.png", "test3");
    LoadSurface("assets/thing.png", "thing");
    TextureFromSurface("test", "test");
    TextureFromSurface("test2", "test2");
    TextureFromSurface("test3", "test3");
    TextureFromSurface("thing", "thing");

    LoadSurface("assets/butter.png", "butter");
    TextureFromSurface("butter", "butter");

    LoadSurface("assets/background.png", "background");
    TextureFromSurface("background", "background");
}

CDrawing::~CDrawing() {
    for (auto& Surface : m_aSurfaces)
        SDL_FreeSurface(Surface.second);

    for (auto& Texture : m_aTextures)
        SDL_DestroyTexture(Texture.second);
}

SDL_Surface* CDrawing::LoadSurface(const char* filepath, const char* key) {
    SDL_Surface* NewSurface = GetSurface(key);
    if (NewSurface) return NewSurface;

    NewSurface = IMG_Load(filepath);
    m_aSurfaces[key] = NewSurface;

    if (!NewSurface) std::cout << SDL_GetError() << std::endl;

    return NewSurface;
}

SDL_Surface* CDrawing::GetSurface(const char* key) {
    for (auto& Surface : m_aSurfaces)
        if (strcmp(Surface.first, key) == 0)
            return Surface.second;
    return nullptr;
}

SDL_Texture* CDrawing::TextureFromSurface(const char* surface_key, const char* key) {
    SDL_Surface* FromSurface = GetSurface(surface_key);
    if (!FromSurface) {
        std::cout << "Couldn't convert " << surface_key << " to texture (nullptr)" << std::endl;
        return nullptr;
    }

    SDL_Texture* NewTexture = GetTexture(key);
    if (NewTexture)
        return NewTexture;

    NewTexture = SDL_CreateTextureFromSurface(m_pRenderer, FromSurface);
    m_aTextures[key] = NewTexture;
    return NewTexture;
}

SDL_Texture* CDrawing::GetTexture(const char* key) {
    for (auto& Texture : m_aTextures)
        if (strcmp(Texture.first, key) == 0)
            return Texture.second;
    return nullptr;
}

void CDrawing::Clear() {
    SDL_RenderClear(m_pRenderer);
}

void CDrawing::Present() {
    SDL_RenderPresent(m_pRenderer);
}

void CDrawing::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void CDrawing::SetColor(SDL_Color color) {
    SetColor(color.r, color.g, color.b, color.a);
}

void CDrawing::RenderCopy(SDL_Texture* pTexture, SDL_Rect* srcrect, SDL_Rect* dstrect, bool translate) {
    if (translate && m_pCamera && dstrect) m_pCamera->Translate(&dstrect->x, &dstrect->y);
    SDL_RenderCopy(m_pRenderer, pTexture, srcrect, dstrect);
}

void CDrawing::FillRect(SDL_Rect Rect, bool translate) {
    if (translate && m_pCamera) m_pCamera->Translate(&Rect.x, &Rect.y);

    SDL_RenderFillRect(m_pRenderer, &Rect);
}

void CDrawing::FillRect(int x, int y, int w, int h, bool translate) {
    if (translate && m_pCamera) m_pCamera->Translate(&x, &y);
    SDL_Rect Rect = { x, y, w, h };

    SDL_RenderFillRect(m_pRenderer, &Rect);
}

void CDrawing::FillRect(double x, double y, double w, double h, bool translate) {
    if (translate && m_pCamera) m_pCamera->Translate(&x, &y);
    SDL_Rect Rect = { (int)x, (int)y, (int)w, (int)h };

    SDL_RenderFillRect(m_pRenderer, &Rect);
}

void CDrawing::ReverseTranslate(int* outx, int* outy) {
    if (!m_pCamera) return;
    m_pCamera->ReverseTranslate(outx, outy);
}

void CDrawing::ReverseTranslate(double* outx, double* outy) {
    if (!m_pCamera) return;
    m_pCamera->ReverseTranslate(outx, outy);
}

void CDrawing::SetCamera(CCamera* pCamera) {
    m_pCamera = pCamera;
}
