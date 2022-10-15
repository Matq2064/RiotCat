#include "Gameworld.h"

CGameWorld::CGameWorld(CWindow* pWindow, int width, int height) {
    m_pWindow = pWindow;
    m_pTilemap = new CTileMap(pWindow, width, height);
    m_pTilemap->LoadMap("MyFirstMap.rc");
}

CGameWorld::~CGameWorld() {
    delete m_pTilemap;
}

void CGameWorld::Tick() {
    m_pTilemap->Tick();
}

void CGameWorld::Draw() {
    m_pTilemap->Draw();
}

void CGameWorld::SpawnCoordinates(double* x, double* y) {
    m_pTilemap->FindTileWorld(TileType::TILE_SPAWNPOINT, x, y);
}
