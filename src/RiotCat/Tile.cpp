#include "Tile.h"

SDL_Color TileColor(TileType type) {
    switch (type) {
        default:
        case TILE_SOLID:
            return SDL_Color{ 255, 0, 0, 255 };
    }
}

CTile::CTile() {
    m_Type = TileType::TILE_EMPTY;
}

CTileMap::CTileMap(CWindow* pWindow, int width, int height) {
    m_pWindow = pWindow;
    m_Width = width;
    m_Height = height;

    int Area = width * height;
    m_aTiles = new CTile[Area];
}

CTileMap::~CTileMap() {
    delete[] m_aTiles;
}

void CTileMap::Draw() {
    CDrawing* pDrawing = m_pWindow->Drawing();

    for (int i = 0; i < m_Width * m_Height; i++) {
        int x = i % m_Width;
        int y = i / m_Height;
        CTile* pTile = &m_aTiles[i];
        TileType Type = pTile->Type();

        if (Type == TILE_EMPTY)
            continue;

        SDL_Color Color = TileColor(Type);
        pDrawing->SetColor(Color);

        SDL_Rect Rect;
        Rect.x = x * m_TileSize;
        Rect.y = y * m_TileSize;
        Rect.w = m_TileSize;
        Rect.h = m_TileSize;
        pDrawing->FillRect(&Rect);
    }
}
