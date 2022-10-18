#include "Clock.h"
#include <iostream>
using namespace std;

CClock::CClock(SDL_Window* pWindow, CDrawing* pDrawing, CInput* pInput, double frequency)
{
    m_pWindow = pWindow;
    m_pDrawing = pDrawing;
    m_pInput = pInput;
    m_Frequency = frequency;
    m_PeriodDelay = 1.0 / frequency;

    m_pFont = TTF_OpenFont("Robot Crush.ttf", 24);
    m_pInput->AddKey(SDL_SCANCODE_LEFT);
    m_pInput->AddKey(SDL_SCANCODE_RIGHT);

    cout << TTF_GetError() << endl;
}

void CClock::Draw() {
    int Width, Height;
    SDL_GetWindowSize(m_pWindow, &Width, &Height);

    SDL_Color Green = { 0, 255, 0, 255 };
    SDL_Color Red = { 155, 0, 0, 255 };
    char fps_msg[64], locked_msg[64];
    snprintf(locked_msg, sizeof(locked_msg), "FPS: %i", (int)m_Frequency);
    snprintf(fps_msg, sizeof(fps_msg), "%ims", (int)(m_TimeElapsed*1e3));

    SDL_Color FPS_Color = m_TimeElapsed < 1.0 / ((1.0/m_PeriodDelay) - 1.0) ? Green : Red;

    SDL_Surface* Surface = TTF_RenderText_Solid(m_pFont, fps_msg, FPS_Color);
    SDL_Texture* FPS_Texture = SDL_CreateTextureFromSurface(m_pDrawing->Renderer(), Surface);
    SDL_FreeSurface(Surface);
    Surface = TTF_RenderText_Solid(m_pFont, locked_msg, FPS_Color);
    SDL_Texture* LOCKED_Texture = SDL_CreateTextureFromSurface(m_pDrawing->Renderer(), Surface);
    SDL_FreeSurface(Surface);

    SDL_Rect FPS_Rect;
    SDL_QueryTexture(FPS_Texture, nullptr, nullptr, &FPS_Rect.w, &FPS_Rect.h);
    FPS_Rect.x = Width - FPS_Rect.w;
    FPS_Rect.y = 0;

    SDL_Rect LOCKED_Rect;
    SDL_QueryTexture(LOCKED_Texture, nullptr, nullptr, &LOCKED_Rect.w, &LOCKED_Rect.h);
    LOCKED_Rect.x = Width - LOCKED_Rect.w;
    LOCKED_Rect.y = FPS_Rect.y + FPS_Rect.h;

    SDL_RenderCopy(m_pDrawing->Renderer(), FPS_Texture, nullptr, &FPS_Rect);
    SDL_RenderCopy(m_pDrawing->Renderer(), LOCKED_Texture, nullptr, &LOCKED_Rect);

    SDL_DestroyTexture(FPS_Texture);
    SDL_DestroyTexture(LOCKED_Texture);
}

void CClock::Begin()
{
    m_Begin = chrono::steady_clock::now();
}

void CClock::End()
{
    m_End = chrono::steady_clock::now();
    m_TimeElapsed = (double)(chrono::duration_cast<chrono::nanoseconds>(m_End - m_Begin).count()) * 1e-9;
}

void CClock::Tick() {
    bool Left = m_pInput->GetKey(SDL_SCANCODE_LEFT);
    bool Right = m_pInput->GetKey(SDL_SCANCODE_RIGHT);

    if (Left != Right) {
        if (Left) m_Frequency--;
        else m_Frequency++;

        if (m_Frequency < 1.0)
            m_Frequency = 1.0;

        m_PeriodDelay = 1.0 / m_Frequency;
    }

    do { End(); }
    while (m_TimeElapsed < m_PeriodDelay);
}
