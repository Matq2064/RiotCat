#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
#include "RiotCat/Gameworld.h"
#include "RiotCat/Character.h"

#include <SDL_ttf.h>
#include <iostream>
using namespace std;

CWindow* pWindow;
CGameWorld* pGameworld;
CCharacter* pCharacter;

int main() {
    SDL_Init(0);
    TTF_Init();
    pWindow = new CWindow("RiotCat", 900, 700);
    if (!pWindow->Initialized())
        return -1;

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();

    pGameworld = new CGameWorld(pWindow, 20, 20);
    pCharacter = new CCharacter(pGameworld);

    while (true) {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pGameworld->Tick();
        pCharacter->Tick();

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();

        pGameworld->Draw();
        pCharacter->Draw();
        pClock->Draw();

        pDrawing->Present();
        pClock->Tick();
    }

    delete pCharacter;
    delete pGameworld;
    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
