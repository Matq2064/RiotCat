#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
using namespace std;

int WIDTH = 900;
int HEIGHT = 700;
CWindow* pWindow;

int main() {
    pWindow = new CWindow("RiotCat Editor", WIDTH, HEIGHT);
    if (!pWindow->Initialized())
        return -1;

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();
    while (true)
    {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();
        pDrawing->Present();

        do { pClock->End(); }
        while (pClock->TimeElapsed() < 1.0 / 75.0);
    }

    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
