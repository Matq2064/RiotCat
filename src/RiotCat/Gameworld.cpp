#include "Gameworld.h"

CGameWorld::CGameWorld(CWindow* pWindow, int width, int height) {
    m_pWindow = pWindow;
    m_pTilemap = new CTileMap(pWindow, width, height, false);
    m_pTilemap->LoadMap("MyFirstMap.rc");
    m_Finished = false;
    m_pSpagetti = pWindow->Drawing()->GetTexture("spagetti");
}

CGameWorld::~CGameWorld() {
    delete m_pTilemap;
}

void CGameWorld::Tick() {
    m_pTilemap->Tick();
}

void CGameWorld::Draw() {
    m_pTilemap->Draw();
    if (m_Finished)
        m_pWindow->Drawing()->RenderCopy(m_pSpagetti, nullptr, nullptr, false);
}

void CGameWorld::SpawnCoordinates(double* x, double* y) {
    m_pTilemap->FindTileWorld(TileType::TILE_SPAWNPOINT, x, y);
}
