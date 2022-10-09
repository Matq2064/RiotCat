#include "ETilemap.h"

CETileMap::CETileMap(CWindow *pWindow, int width, int height)
    : CTileMap(pWindow, width, height) {
    m_pWindow->Input()->AddObject(this);
}

CETileMap::~CETileMap() {
    m_pWindow->Input()->RemoveObject(this);
}
