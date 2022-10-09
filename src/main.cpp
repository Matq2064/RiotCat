#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
#include "RiotCat/Character.h"
using namespace std;

int WIDTH = 900;
int HEIGHT = 700;
CWindow* pWindow;
CCharacter* pCharacter;

int main() {
    pWindow = new CWindow("RiotCat", WIDTH, HEIGHT);
    if (!pWindow->Initialized())
        return -1;

    pCharacter = new CCharacter(300, 300);
    pWindow->Input()->AddObject(pCharacter);

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();
    while (true)
    {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pCharacter->Tick(pClock->TimeElapsed());

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();
        pCharacter->Draw(pDrawing);
        pDrawing->Present();

        do { pClock->End(); }
        while (pClock->TimeElapsed() < 1.0 / 75.0);
    }

    delete pCharacter;
    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
