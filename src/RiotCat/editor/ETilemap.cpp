#include "ETilemap.h"
#include <math.h>

CETileMap::CETileMap(CWindow *pWindow, int width, int height)
    : CTileMap(pWindow, width, height, true) {
    m_CurrentTile = TILES_EDITOR;

    CInput* pInput = m_pWindow->Input();
    pInput->AddButton(SDL_BUTTON_RIGHT);
    pInput->AddButton(SDL_BUTTON_LEFT);
    pInput->AddKey(SDL_SCANCODE_O);
    pInput->AddKey(SDL_SCANCODE_P);
    pInput->AddKey(SDL_SCANCODE_UP);
    pInput->AddKey(SDL_SCANCODE_RIGHT);
    pInput->AddKey(SDL_SCANCODE_DOWN);
    pInput->AddKey(SDL_SCANCODE_LEFT);
    pInput->AddKey(SDL_SCANCODE_LSHIFT);
}

CETileMap::~CETileMap() {

}

void CETileMap::Tick() {
    CDrawing* pDrawing = m_pWindow->Drawing();
    CInput* pInput = m_pWindow->Input();

    bool Save = pInput->GetKeyTap(SDL_SCANCODE_O);
    bool Load = pInput->GetKeyTap(SDL_SCANCODE_P);
    bool HeightDown = pInput->GetKeyTap(SDL_SCANCODE_UP);
    bool WidthUp = pInput->GetKeyTap(SDL_SCANCODE_RIGHT);
    bool HeightUp = pInput->GetKeyTap(SDL_SCANCODE_DOWN);
    bool WidthDown = pInput->GetKeyTap(SDL_SCANCODE_LEFT);
    bool LClick = pInput->GetButton(SDL_BUTTON_LEFT);
    bool RClick = pInput->GetButton(SDL_BUTTON_RIGHT);
    int Scroll = pInput->ScrollDirection();

    if (Save) SaveMap("MyFirstMap.rc");
    if (Load) LoadMap("MyFirstMap.rc");

    bool NewWidth = WidthUp != WidthDown;
    bool NewHeight = HeightUp != HeightDown;

    if (NewWidth) {
        if (WidthUp) Resize(m_Width + 1, m_Height);
        else Resize(m_Width - 1, m_Height);
    } else if (NewHeight) {
        if (HeightUp) Resize(m_Width, m_Height + 1);
        else Resize(m_Width, m_Height - 1);
    }

    m_CurrentTile = (TileType)(m_CurrentTile + Scroll);
    if (m_CurrentTile < TILES_EDITOR) m_CurrentTile = (TileType)(NUM_TILES - 1);
    else if (m_CurrentTile >= NUM_TILES) m_CurrentTile = TILES_EDITOR;

    if (LClick || RClick) {
        TileType Type;
        if (LClick) Type = m_CurrentTile;
        else Type = TILE_EMPTY;

        int StartX, StartY, EndX, EndY;
        pInput->GetLastMousePos(&StartX, &StartY);
        pInput->GetMousePos(&EndX, &EndY);

        pDrawing->ReverseTranslate(&StartX, &StartY);
        pDrawing->ReverseTranslate(&EndX, &EndY);

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

                m_aTiles[y * m_Width + x] = ParseTile(Type);
            }
        }
        int x = (int)((double)EndX / m_TileSize);
        int y = (int)((double)EndY / m_TileSize);
        if (x < 0) x = 0;
        if (x >= m_Width) x = m_Width - 1;
        if (y < 0) y = 0;
        if (y >= m_Height) y = m_Height - 1;

        m_aTiles[y * m_Width + x] = ParseTile(Type);
    }
}

