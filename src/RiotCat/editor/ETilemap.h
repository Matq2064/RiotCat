#ifndef RIOTCAT_ETILEMAP_H
#define RIOTCAT_ETILEMAP_H

#include "../Tile.h"
#include <map>

class CETileMap : public CTileMap {
private:
    TileType m_CurrentTile;

public:
    CETileMap(CWindow* pWindow, int width, int height);
    ~CETileMap();

    void Tick();
};

#endif //RIOTCAT_ETILEMAP_H
