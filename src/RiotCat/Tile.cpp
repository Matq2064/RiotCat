#include "Tile.h"
#include "Files.h"

CTile CTileMap::ParseTile(TileType type) {
    switch (type) {
        case TILE_INVALID:
        default: return {};
        case TILE_EMPTY: return CTileEmpty();
        case TILE_SOLID: return CTileSolid();
        case TILE_DEATH: return CTileDeath();
        case TILE_SPAWNPOINT: return CTileSpawnpoint();
    }
}

CTileMap::CTileMap(CWindow* pWindow, int width, int height, bool editor) {
    m_pWindow = pWindow;
    m_Width = width;
    m_Height = height;
    m_Editor = editor;

    m_aTiles = new CTile[m_Width * m_Height];
    for (int i = 0; i < m_Width * m_Height; i++)
        m_aTiles[i] = ParseTile(TILE_EMPTY);

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

        TileVisibility Visibility = pTile->Visibility();
        if (Visibility == VISIBLE_NO || !m_Editor && Visibility == VISIBLE_EDITOR)
            continue;

        SDL_Color Color = pTile->Color();
        pDrawing->SetColor(Color);

        SDL_Rect Rect;
        Rect.x = x * m_TileSize;
        Rect.y = y * m_TileSize;
        Rect.w = m_TileSize;
        Rect.h = m_TileSize;
        pDrawing->FillRect(Rect, true);
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

#include <iostream>
using namespace std;

void CTileMap::LoadMap(const char* filepath) {
    CReadFiles Mapfile(filepath);
    if (Mapfile.Error())
        return;

    m_Width = Mapfile.GetInt();
    m_Height = Mapfile.GetInt();

    for (int i = 0; i < m_Width * m_Height; i++)
        m_aTiles[i] = ParseTile((TileType) Mapfile.GetInt());

    Mapfile.Close();
}

void CTileMap::FindTileWorld(TileType type, double* outx, double* outy) {
    int tilex, tiley;
    FindTile(type, &tilex, &tiley);

    *outx = ((double)(tilex) + 0.5) * m_TileSize;
    *outy = ((double)(tiley) + 0.5) * m_TileSize;
}

void CTileMap::FindTile(TileType type, int* outx, int* outy) {
    for (int i = 0; i < m_Width * m_Height; i++) {
        TileType Type = m_aTiles[i].GetType();
        if (Type != type) continue;

        *outx = i % m_Width;
        *outy = i / m_Width;
    }
}

CTile* CTileMap::GetTileWorld(double x, double y) {
    x /= m_TileSize;
    y /= m_TileSize;

    return GetTile((int)x, (int)y);
}


CTile* CTileMap::GetTile(int tilex, int tiley) {
    if (tilex < 0) tilex = 0;
    if (tilex >= m_Width) tilex = m_Width - 1;
    if (tiley < 0) tiley = 0;
    if (tiley >= m_Height) tiley = m_Height - 1;

    return &m_aTiles[tiley * m_Width + tilex];
}

double CTileMap::TileHighFace(double v) {
    return TileLowFace(v) + m_TileSize;
}

double CTileMap::TileLowFace(double v) {
    return (double)((int)(v / (double)m_TileSize) * m_TileSize);
}

void CTileMap::Resize(int width, int height) {
    CTile* aNewTiles = new CTile[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int NewIndex = y * width + x;
            if(x >= m_Width || y >= m_Height) { aNewTiles[NewIndex].SetType(TILE_DEATH); }
            else {
                int OldIndex = y * m_Width + x;
                TileType Type = m_aTiles[OldIndex].GetType();

                aNewTiles[NewIndex].SetType(Type);
            }
        }
    }

    m_Width = width;
    m_Height = height;

    delete[] m_aTiles;
    m_aTiles = aNewTiles;
}
