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

void CDrawing::FillRect(SDL_Rect* pRect) {
    SDL_RenderFillRect(m_pRenderer, pRect);
}
