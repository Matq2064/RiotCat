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

    TileType Type() const { return m_Type; }
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
};

#endif //RIOTCAT_TILE_H
