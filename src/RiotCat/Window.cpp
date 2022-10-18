#include "Window.h"
#include <iostream>

CWindow::CWindow(const char* title, int width, int height)
{
    SDL_WindowFlags flags = SDL_WINDOW_SHOWN;
    m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (m_pWindow == nullptr)
        printf("Failed to initialize SDL_Window: %s\n", SDL_GetError());

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == nullptr)
        printf("Failed to initialize SDL_Renderer: %s\n", SDL_GetError());

    m_pInput = new CInput();
    m_pDrawing = new CDrawing(m_pRenderer);
    m_pClock = new CClock(m_pWindow, m_pDrawing, m_pInput, 244.0);

    if (m_pWindow && m_pRenderer)
        m_Initialized = true;
}

CWindow::~CWindow()
{
    delete m_pClock;
    delete m_pInput;
    delete m_pDrawing;
    if (m_pRenderer) SDL_DestroyRenderer(m_pRenderer);
    if (m_pWindow) SDL_DestroyWindow(m_pWindow);
}
