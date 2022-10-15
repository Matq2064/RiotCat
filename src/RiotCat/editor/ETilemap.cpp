#include "ETilemap.h"

CETileMap::CETileMap(CWindow *pWindow, int width, int height)
    : CTileMap(pWindow, width, height) {
    CInput* pInput = m_pWindow->Input();
    pInput->AddButton(SDL_BUTTON_LEFT);
    pInput->AddButton(SDL_BUTTON_MIDDLE);
    pInput->AddButton(SDL_BUTTON_RIGHT);
    pInput->AddKey(SDL_SCANCODE_O);
    pInput->AddKey(SDL_SCANCODE_P);
}

CETileMap::~CETileMap() {

}

void CETileMap::Tick() {
    CInput* pInput = m_pWindow->Input();

    if (pInput->GetKeyTap(SDL_SCANCODE_O))
        SaveMap("MyFirstMap.rc");
    if (pInput->GetKeyTap(SDL_SCANCODE_P))
        LoadMap("MyFirstMap.rc");

    bool LClick = pInput->GetButton(SDL_BUTTON_LEFT);
    bool MClick = pInput->GetButton(SDL_BUTTON_MIDDLE);
    bool RClick = pInput->GetButton(SDL_BUTTON_RIGHT);
    if (LClick || MClick || RClick) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        x /= m_TileSize;
        y /= m_TileSize;

        if (x >= m_Width || y >= m_Height)
            return;

        TileType Type;
        if (LClick) Type = TILE_SOLID;
        else if (MClick) Type = TILE_SPAWNPOINT;
        else Type == TILE_EMPTY;
        m_aTiles[y * m_Width + x].SetType(Type);
    }
}

