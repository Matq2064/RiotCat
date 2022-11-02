#ifndef RIOTCAT_TILE_H
#define RIOTCAT_TILE_H

#include "Window.h"

enum TileVisibility {
    VISIBLE_NO,
    VISIBLE_YES,
    VISIBLE_EDITOR
};

enum TileType {
    TILE_INVALID = -1,
    TILE_EMPTY,
    TILES_EDITOR,
    TILE_SOLID = TILES_EDITOR,
    TILE_DEATH,
    TILE_SPAWNPOINT,
    NUM_TILES
};

class CTile {
protected:
    TileType m_Type;
    TileVisibility m_Visibility;
    bool m_Collides;
    SDL_Color m_Color;

public:
    CTile() {
        m_Type = TileType::TILE_INVALID;
        m_Visibility = TileVisibility::VISIBLE_YES;
        m_Collides = false;
        m_Color = { 255, 0, 255, 50 };
    }

    TileType GetType() const { return m_Type; }
    TileVisibility Visibility() const { return m_Visibility; }
    bool Collides() const { return m_Collides; }
    SDL_Color Color() const { return m_Color; }
    void SetType(TileType type) { m_Type = type; }
};

class CTileEmpty : public CTile {
public:
    CTileEmpty() {
        m_Type = TILE_EMPTY;
        m_Visibility = VISIBLE_NO;
        m_Collides = false;
    }

};

class CTileSolid : public CTile {
public:
    CTileSolid() {
        m_Type = TILE_SOLID;
        m_Visibility = VISIBLE_YES;
        m_Collides = true;
        m_Color = { 150, 0, 150, 255 };
    }
};

class CTileDeath : public CTile {
public:
    CTileDeath() {
        m_Type = TILE_DEATH;
        m_Visibility = VISIBLE_YES;
        m_Collides = false;
        m_Color = { 255, 0, 0, 255 };
    }
};

class CTileSpawnpoint : public CTile {
public:
    CTileSpawnpoint() {
        m_Type = TILE_SPAWNPOINT;
        m_Visibility = VISIBLE_EDITOR;
        m_Collides = false;
        m_Color = { 0, 255, 0, 255 };
    }
};

class CTileMap {
protected:
    CWindow* m_pWindow;
    const int m_TileSize = 32;
    int m_Width, m_Height;
    bool m_Editor;
    CTile* m_aTiles;

    CTile ParseTile(TileType type);

public:
    CTileMap(CWindow* pWindow, int width, int height, bool editor);
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
