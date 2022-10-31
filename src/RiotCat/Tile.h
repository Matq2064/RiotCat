#ifndef RIOTCAT_TILE_H
#define RIOTCAT_TILE_H

#include "Window.h"

enum TileType {
    TILE_EMPTY = -1,
    TILE_SOLID,
    TILE_DEATH,
    TILE_SPAWNPOINT,
    NUM_TILES
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
    void FindTileWorld(TileType type, double* outx, double* outy);
    void FindTile(TileType type, int* outx, int* outy);
    CTile* GetTileWorld(double x, double y);
    CTile* GetTile(int tilex, int tiley);
    double TileHighFace(double v);
    double TileLowFace(double v);
    void Resize(int width, int height);
    int TileSize() const { return m_TileSize; }
};

#endif //RIOTCAT_TILE_H
