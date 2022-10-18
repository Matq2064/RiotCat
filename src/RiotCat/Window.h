#ifndef RIOTCAT_WINDOW_H
#define RIOTCAT_WINDOW_H

#include "Input.h"
#include "Drawing.h"
#include "Clock.h"

class CWindow
{
private:
    SDL_Window* m_pWindow = nullptr;
    SDL_Renderer* m_pRenderer = nullptr;
    CInput* m_pInput = nullptr;
    CDrawing* m_pDrawing = nullptr;
    CClock* m_pClock = nullptr;
    bool m_Initialized = false;

public:
    CWindow(const char* title, int width, int height);
    ~CWindow();

    SDL_Window* Window() const { return m_pWindow; }
    SDL_Renderer* Renderer() const { return m_pRenderer; }
    CClock* Clock() const { return m_pClock; }
    CInput* Input() const { return m_pInput; }
    CDrawing* Drawing() const { return m_pDrawing; }
    bool Initialized() const { return m_Initialized; }
    void GetSize(int* w, int* h) const { SDL_GetWindowSize(Window(), w, h); };
};


#endif //RIOTCAT_WINDOW_H
