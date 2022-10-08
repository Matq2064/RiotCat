#include "Tiles.h"

CTiles::CTiles() {

}

CTiles::CTiles(int width, int height) {
    m_width = width;
    m_height = height;

    int Area_ = Area();
    for (int i = 0; i < Area_; i++)
        m_aTiles[i] = DEFAULT;

}

void CTiles::Draw(CDrawing* pDrawing) {
    for (int i = 0; i < Area(); i++) {
        int TileX = i % Width();
        int TileY = i / Height();

        int TileID = m_aTiles[i];
        switch (TileID) {
            case TILE_NONE:
                continue;
            case TILE_SOMETHING: {
                pDrawing->SetColor(255, 255, 255, 255);
            } break;
            case TILE_DETH: {
                pDrawing->SetColor(255, 0, 0, 255);
            } break;
        }

        SDL_Rect Rect;
        Rect.x = TileX * m_TileSize;
        Rect.y = TileY * m_TileSize;
        Rect.w = m_TileSize;
        Rect.h = m_TileSize;
        pDrawing->FillRect(&Rect);
    }
}

void CTiles::Input(SDL_Event& Event) {
    if (Event.type != SDL_KEYDOWN)
        return;

    if (Event.key.keysym.scancode == SDL_SCANCODE_S)
        SaveMap("MyFirstMap.rc");
    else if (Event.key.keysym.scancode == SDL_SCANCODE_L)
        LoadMap("MyFirstMap.rc");
}

bool CTiles::SaveMap(const char* filepath) {
    ofstream File(filepath, ios::binary);
    if (!File.is_open()) {
        printf("Couldn't open file: %s\n", filepath);
        return false;
    }

    CWriteFiles Map(filepath);
    Map.AddInt(m_width);
    Map.AddInt(m_height);
    for (int i = 0; i < Area(); i++)
        Map.AddInt(m_aTiles[i]);

    File.close();
    return true;
}

bool CTiles::LoadMap(const char* filepath) {
    ifstream File(filepath, ios::binary);
    if (!File.is_open()) {
        printf("Couldn't open file: %s\n", filepath);
        return false;
    }

    CReadFiles Map(filepath);
    m_width = Map.GetInt();
    m_height = Map.GetInt();
    for (int i = 0; i < Area(); i++)
        m_aTiles[i] = Map.GetInt();

    File.close();
    return true;
}
