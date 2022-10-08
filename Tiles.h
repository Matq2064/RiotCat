#ifndef RIOTCATE_TILES_H
#define RIOTCATE_TILES_H

#include "Files.h"
#include "Input.h"
#include "Drawing.h"

class CTiles : public CHandleInput {
private:
    int m_TileSize = 32;
    int m_width, m_height;
    int m_aTiles[1048576]; // 4 Megabytes nexup do dynamic sizes wooooo :D :D

    enum TileType {
        TILE_NONE,
        TILE_SOMETHING,
        TILE_DETH,
        NUM_TILES,
        DEFAULT = TILE_NONE,
    };

public:
    CTiles();
    CTiles(int width, int height);

    int Width() const { return m_width; }
    int Height() const { return m_height; }
    int Area() const { return Width() * Height(); }
    void Draw(CDrawing* pDrawing);
    void Input(SDL_Event& Event);
    bool SaveMap(const char* filepath);
    bool LoadMap(const char* filepath);
};

#endif //RIOTCATE_TILES_H
