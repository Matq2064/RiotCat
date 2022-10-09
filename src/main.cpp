#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
#include "RiotCat/Character.h"
using namespace std;

CWindow* pWindow;
CCharacter* pCharacter;

int main() {
    pWindow = new CWindow("RiotCat", 900, 700);
    if (!pWindow->Initialized())
        return -1;

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();

    pCharacter = new CCharacter(pWindow, 300, 300);
    pInput->AddObject(pCharacter);

    while (true) {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pCharacter->Tick(pClock->TimeElapsed());

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();
        pCharacter->Draw();
        pDrawing->Present();

        do { pClock->End(); }
        while (pClock->TimeElapsed() < 1.0 / 75.0);
    }

    delete pCharacter;
    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
