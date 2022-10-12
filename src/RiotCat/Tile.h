#ifndef RIOTCAT_TILE_H
#define RIOTCAT_TILE_H

#include "Window.h"

enum TileType {
    TILE_EMPTY,
    TILE_SOLID
};

SDL_Color TileColor(TileType type);

class CTile {
private:
    TileType m_Type;

public:
    CTile();

    TileType GetType() const { return m_Type; }
    void SetType(TileType type) { m_Type = type; }
};

class CTileMap {
protected:
    CWindow* m_pWindow;
    const int m_TileSize = 32;
    int m_Width, m_Height;
    CTile* m_aTiles;

public:
    CTileMap(CWindow* pWindow, int width, int height);
    ~CTileMap();

    virtual void Draw();
    void Tick();

    void SaveMap(const char* filepath);
    void LoadMap(const char* filepath);
};

#endif //RIOTCAT_TILE_H
