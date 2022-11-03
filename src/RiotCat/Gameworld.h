#ifndef RIOTCAT_GAMEWORLD_H
#define RIOTCAT_GAMEWORLD_H

#include "Tile.h"

#define GRAVITY 1500

class CWindow;
class CGameWorld {
private:
    CWindow* m_pWindow;
    CTileMap* m_pTilemap;
    bool m_Finished;
    SDL_Texture* m_pSpagetti;

public:
    CGameWorld(CWindow* pWindow, int width, int height);
    ~CGameWorld();

    void Tick();
    void Draw();
    void SpawnCoordinates(double* x, double* y);
    void SetFinished(bool state) { m_Finished = state; }
    CWindow* Window() const { return m_pWindow; }
    CTileMap* TileMap() const { return m_pTilemap; }
    bool Finished() const { return m_Finished; }
};

#endif //RIOTCAT_GAMEWORLD_H
