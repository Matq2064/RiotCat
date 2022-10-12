#include "Gameworld.h"

CGameWorld::CGameWorld(CWindow* pWindow, int width, int height) {
    m_pWindow = pWindow;
    m_pTilemap = new CTileMap(pWindow, width, height);
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
