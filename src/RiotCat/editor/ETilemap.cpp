#include "ETilemap.h"
#include <math.h>

CETileMap::CETileMap(CWindow *pWindow, int width, int height)
    : CTileMap(pWindow, width, height) {
    m_CurrentTile = (TileType)0;

    CInput* pInput = m_pWindow->Input();
    pInput->AddButton(SDL_BUTTON_LEFT);
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

    m_CurrentTile = (TileType)(m_CurrentTile + pInput->ScrollDirection());
    if (m_CurrentTile < 0) m_CurrentTile = (TileType)(NUM_TILES - 1);
    else if (m_CurrentTile >= NUM_TILES) m_CurrentTile = (TileType)0;

    bool LClick = pInput->GetButton(SDL_BUTTON_LEFT);
    bool RClick = pInput->GetButton(SDL_BUTTON_RIGHT);
    if (LClick || RClick) {
        TileType Type;
        if (LClick) Type = m_CurrentTile;
        else Type = TILE_EMPTY;

        int StartX, StartY, EndX, EndY;
        pInput->GetLastMousePos(&StartX, &StartY);
        pInput->GetMousePos(&EndX, &EndY);
        int TravelX = EndX - StartX;
        int TravelY = EndY - StartY;
        double Travel = sqrt(pow(TravelX, 2) + pow(TravelY, 2));
        if (Travel > 1.0) {
            double SliceX = TravelX / Travel;
            double SliceY = TravelY / Travel;

            for (int i = 0; i < (int)Travel; i++) {
                int CurrentX = (int)(StartX + SliceX * i);
                int CurrentY = (int)(StartY + SliceY * i);

                int x = (int)((double)CurrentX / m_TileSize);
                int y = (int)((double)CurrentY / m_TileSize);
                if (x < 0) x = 0;
                if (x >= m_Width) x = m_Width - 1;
                if (y < 0) y = 0;
                if (y >= m_Height) y = m_Height - 1;

                m_aTiles[y * m_Width + x].SetType(Type);
            }
        }
        int x = (int)((double)EndX / m_TileSize);
        int y = (int)((double)EndY / m_TileSize);
        if (x < 0) x = 0;
        if (x >= m_Width) x = m_Width - 1;
        if (y < 0) y = 0;
        if (y >= m_Height) y = m_Height - 1;

        m_aTiles[y * m_Width + x].SetType(Type);
    }
}

