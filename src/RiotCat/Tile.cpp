#include "Tile.h"
#include "Files.h"

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

    m_aTiles = new CTile[m_Width * m_Height];
    m_pWindow->Input()->AddKey(SDL_SCANCODE_P);
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
        TileType Type = pTile->GetType();

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

void CTileMap::Tick() {
    CInput* pInput = m_pWindow->Input();
    if (pInput->GetKeyTap(SDL_SCANCODE_P))
        LoadMap("MyFirstMap.rc");
}

void CTileMap::SaveMap(const char* filepath) {
    CWriteFiles Mapfile(filepath);
    if (Mapfile.Error())
        return;

    Mapfile.AddInt(m_Width);
    Mapfile.AddInt(m_Height);

    for (int i = 0; i < m_Width * m_Height; i++)
        Mapfile.AddInt((int)m_aTiles[i].GetType());
    Mapfile.Close();
}

void CTileMap::LoadMap(const char* filepath) {
    CReadFiles Mapfile(filepath);
    if (Mapfile.Error())
        return;

    m_Width = Mapfile.GetInt();
    m_Height = Mapfile.GetInt();

    for (int i = 0; i < m_Width * m_Height; i++)
        m_aTiles[i].SetType((TileType)Mapfile.GetInt());
    Mapfile.Close();

    printf("loaded map\n");
}
