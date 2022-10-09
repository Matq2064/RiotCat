#ifndef RIOTCAT_ETILEMAP_H
#define RIOTCAT_ETILEMAP_H

#include "../Tile.h"

class CETileMap : public CTileMap, CHandleInput {
private:

public:
    CETileMap(CWindow* pWindow, int width, int height);
    ~CETileMap();

    // void Input(); becuz CHandleInput lawlz
};

#endif //RIOTCAT_ETILEMAP_H
