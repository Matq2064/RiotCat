#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
#include "RiotCat/editor/ETilemap.h"
using namespace std;

CWindow* pWindow;
CETileMap* pTilemap;

int main() {
    SDL_Init(0);
    TTF_Init();
    pWindow = new CWindow("RiotCat", 900, 700);
    if (!pWindow->Initialized())
        return -1;

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();

    pTilemap = new CETileMap(pWindow, 20, 20);
    pTilemap->LoadMap("MyFirstMap.rc");

    while (true) {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pTilemap->Tick();

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();

        pTilemap->Draw();
        pClock->Draw();

        pDrawing->Present();
        pClock->Tick();
    }

    delete pTilemap;
    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
