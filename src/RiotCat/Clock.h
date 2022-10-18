#ifndef RIOTCAT_CLOCK_H
#define RIOTCAT_CLOCK_H

#include "Drawing.h"
#include "Input.h"
#include <chrono>

using namespace std;

class CClock
{
private:
    SDL_Window* m_pWindow;
    CDrawing* m_pDrawing;
    CInput* m_pInput;
    TTF_Font* m_pFont;
    double m_Frequency = -1.0;
    double m_TimeElapsed = 0.0;
    double m_PeriodDelay = 0.0;
    chrono::steady_clock::time_point m_Begin, m_End;

public:
    CClock(SDL_Window* pWindow, CDrawing* pDrawing, CInput* pInput, double frequency);

    void Draw();
    void Begin();
    void End();
    void Tick();
    double TimeElapsed() const { return m_TimeElapsed; }
};

#endif //RIOTCAT_CLOCK_H
