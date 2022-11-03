#define SDL_MAIN_HANDLED

#include "RiotCat/Window.h"
#include "RiotCat/editor/ETilemap.h"
#include "RiotCat/editor/Ghost.h"
using namespace std;

CWindow* pWindow;
CETileMap* pTilemap;
CCamera* pCamera;
CGhost* pGhost;

int main() {
    SDL_Init(0);
    TTF_Init();
    pWindow = new CWindow("RiotCat", 900, 700);
    if (!pWindow->Initialized())
        return -1;

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();
    CollectTileTextures(pDrawing);
    pCamera = new CCamera(0, 0, 900, 700, FOLLOW_INSTANT);
    pDrawing->SetCamera(pCamera);
    pGhost = new CGhost(pInput, 0, 0);
    pCamera->SetFollow(pGhost);

    pTilemap = new CETileMap(pWindow, 100, 100);
    pTilemap->LoadMap("MyFirstMap.rc");
    pTilemap->FindTileWorld(TileType::TILE_SPAWNPOINT, pGhost->GetXPointer(), pGhost->GetYPointer());

    while (true) {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pTilemap->Tick();
        pGhost->Tick();
        pCamera->Tick();

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();

        pTilemap->Draw();

        pDrawing->Present();
        pClock->Tick();
    }

    delete pGhost;
    delete pCamera;
    delete pTilemap;
    delete pWindow;
    return 0;
}

#undef SDL_MAIN_HANDLED
