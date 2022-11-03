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
    SDL_Texture* pBackground = pDrawing->GetTexture("background");
    int BackgroundWidth, BackgroundHeight;
    SDL_QueryTexture(pBackground, nullptr, nullptr, &BackgroundWidth, &BackgroundHeight);
    CollectTileTextures(pDrawing);
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

        // pDrawing->SetColor(0, 0, 0, 255);
        // pDrawing->Clear();

        // much spagetti its 2am hjelp
        for (int x = (int)(pCamera->GetX() * 0.1) % BackgroundWidth; x < pCamera->GetW() + BackgroundWidth; x += BackgroundWidth) {
            for (int y = (int)(pCamera->GetY() * 0.1) % BackgroundHeight; y < pCamera->GetH() + BackgroundHeight; y += BackgroundHeight) {
                SDL_Rect Destination;
                Destination.x = (int)((double)pCamera->GetW() - x);
                Destination.y = (int)((double)pCamera->GetH() - y);
                Destination.w = BackgroundWidth;
                Destination.h = BackgroundHeight;
                pDrawing->RenderCopy(pBackground, nullptr, &Destination, false);
            }
        }

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
