#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
#include "RiotCat/Gameworld.h"
#include "RiotCat/Character.h"
#include "RiotCat/Camera.h"

#include <SDL_ttf.h>
#include <iostream>
using namespace std;

CWindow* pWindow;
CGameWorld* pGameworld;
CCharacter* pCharacter;
CCamera* pCamera;

int main() {
    SDL_Init(0);
    TTF_Init();
    pWindow = new CWindow("RiotCat", 900, 700);
    if (!pWindow->Initialized())
        return -1;

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();
    pCamera = new CCamera(0, 0, 900, 700, FOLLOW_SLOW);
    pDrawing->SetCamera(pCamera);

    pGameworld = new CGameWorld(pWindow, 100, 100);
    pCharacter = new CCharacter(pGameworld);
    pCharacter->GivePos(pCamera);
    pCamera->SetFollow(pCharacter);

    while (true) {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pGameworld->Tick();
        pCharacter->Tick();
        pCamera->Tick();

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();

        pGameworld->Draw();
        pCharacter->Draw();

        pDrawing->Present();
        pClock->Tick();
    }

    delete pCamera;
    delete pCharacter;
    delete pGameworld;
    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
