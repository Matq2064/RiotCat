#include "Drawing.h"

CDrawing::CDrawing(SDL_Renderer* pRenderer) {
    m_pRenderer = pRenderer;
}

CDrawing::~CDrawing() {

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
