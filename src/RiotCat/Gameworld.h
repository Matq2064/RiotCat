#ifndef RIOTCAT_GAMEWORLD_H
#define RIOTCAT_GAMEWORLD_H

#include "Tile.h"

#define GRAVITY 1500

class CWindow;
class CGameWorld {
private:
    CWindow* m_pWindow;
    CTileMap* m_pTilemap;

public:
    CGameWorld(CWindow* pWindow, int width, int height);
    ~CGameWorld();

    void Tick();
    void Draw();
    void SpawnCoordinates(double* x, double* y);
    CWindow* Window() const { return m_pWindow; }
    CTileMap* TileMap() const { return m_pTilemap; }
};

#endif //RIOTCAT_GAMEWORLD_H
