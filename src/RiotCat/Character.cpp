#include "Character.h"
#include <iostream>
using namespace std;

CCharacter::CCharacter(CGameWorld* pGameworld)
        : CHandleRect(0, 0, 20.0, 30.0) {
    pGameworld->SpawnCoordinates(&m_x, &m_y);
    Initialize(pGameworld);
}

CCharacter::CCharacter(CGameWorld* pGameworld, double x, double y)
        : CHandleRect(x, y, 20.0, 30.0) {
    Initialize(pGameworld);
}

CCharacter::~CCharacter() {

}

void CCharacter::Initialize(CGameWorld* pGameworld) {
    m_pGameworld = pGameworld;
    m_lastx = m_x;
    m_lasty = m_y;
    m_xvel = 0.0;
    m_yvel = 0.0;
    m_Jump = false;

    CInput* pInput = m_pGameworld->Window()->Input();
    pInput->AddKey(SDL_SCANCODE_W);
    pInput->AddKey(SDL_SCANCODE_D);
    pInput->AddKey(SDL_SCANCODE_S);
    pInput->AddKey(SDL_SCANCODE_A);
    pInput->AddKey(SDL_SCANCODE_R);
    pInput->AddKey(SDL_SCANCODE_LEFT);
    pInput->AddKey(SDL_SCANCODE_RIGHT);
    pInput->AddKey(SDL_SCANCODE_UP);
    pInput->AddKey(SDL_SCANCODE_DOWN);
}

void CCharacter::Movement() {
    CInput* pInput = m_pGameworld->Window()->Input();
    CClock* pClock = m_pGameworld->Window()->Clock();
    double DeltaTime = pClock->TimeElapsed();

    bool Jump = pInput->GetKeyTap(SDL_SCANCODE_W);
    bool Right = pInput->GetKey(SDL_SCANCODE_D);
    bool Down = pInput->GetKey(SDL_SCANCODE_S);
    bool Left = pInput->GetKey(SDL_SCANCODE_A);

    double SomeAccel = 2500;
    double Accel = SomeAccel * DeltaTime;
    if (Jump && m_Jump) {
        m_yvel = -1000;
        m_Jump = false;
    }
    if (Down) m_yvel += Accel;

    if (Left != Right) {
        if (Left) m_xvel -= Accel;
        else m_xvel += Accel;
    }
}

void CCharacter::WallCollision() {
    bool ColLeft = m_x - m_w/2 < 0.0;
    bool ColRight = m_x + m_w/2 > 900;
    bool ColUp = m_y - m_h/2 < 0.0;
    bool ColDown = m_y + m_h/2 > 700;

    if (ColLeft || ColRight) {
        m_xvel = 0.0;
        if (ColLeft) m_x = m_w/2;
        else m_x = 900 - m_w/2;
    }
    if (ColUp || ColDown) {
        m_yvel = 0.0;
        if (ColUp) m_y = m_h/2;
        else {
            m_y = 700 - m_h/2;
            m_Jump = true;
        }
    }
}

void CCharacter::TileCollisions() {
    double DestinationX = m_x;
    double DestinationY = m_y;
    m_x = m_lastx;
    m_y = m_lasty;
    double TravelX = DestinationX - m_x;
    double TravelY = DestinationY - m_y;
    double Travel = sqrt(pow(TravelX, 2) + pow(TravelY, 2));
    if (Travel > 0.0) {
        int IntTravel = int(Travel);
        double SliceX = TravelX / (double)IntTravel;
        double SliceY = TravelY / (double)IntTravel;
        double Remainder = Travel - (double)IntTravel;

        for (int j = 0; j < IntTravel; j++) {
            m_x += SliceX;
            m_y += SliceY;
            TileCollision();
        }

        m_x += TravelX / Travel * Remainder;
        m_y += TravelY / Travel * Remainder;
        TileCollision();
    }
}

void CCharacter::TileCollision() {
    CTileMap* pTilemap = m_pGameworld->TileMap();

    double SideLeft = m_x - m_w2;
    double SideRight = m_x + m_w2;
    double SideTop = m_y - m_h2;
    double SideBottom = m_y + m_h2;

    // Corner variables

    bool Deth = pTilemap->GetTileWorld(SideLeft, SideTop)->GetType() == TileType::TILE_DEATH ||
            pTilemap->GetTileWorld(SideRight, SideTop)->GetType() == TileType::TILE_DEATH ||
            pTilemap->GetTileWorld(SideLeft, SideBottom)->GetType() == TileType::TILE_DEATH ||
            pTilemap->GetTileWorld(SideRight, SideBottom)->GetType() == TileType::TILE_DEATH;

    if (Deth) {
        m_pGameworld->TileMap()->FindTileWorld(TileType::TILE_SPAWNPOINT, &m_x, &m_y);
        m_lastx = m_x;
        m_lasty = m_y;
        return;
    }

    bool CornerTopLeft = pTilemap->GetTileWorld(SideLeft, SideTop)->GetType() == TileType::TILE_SOLID;
    bool CornerTopRight = pTilemap->GetTileWorld(SideRight, SideTop)->GetType() == TileType::TILE_SOLID;
    bool CornerBottomLeft = pTilemap->GetTileWorld(SideLeft, SideBottom)->GetType() == TileType::TILE_SOLID;
    bool CornerBottomRight = pTilemap->GetTileWorld(SideRight, SideBottom)->GetType() == TileType::TILE_SOLID;

    // Double corner variables

    bool DoubleTop = CornerTopLeft && CornerTopRight;
    bool DoubleRight = CornerTopRight && CornerBottomRight;
    bool DoubleBottom = CornerBottomLeft && CornerBottomRight;
    bool DoubleLeft = CornerTopLeft && CornerBottomLeft;

    // Wall variables

    bool WallTop = DoubleTop;
    bool WallRight = DoubleRight;
    bool WallBottom = DoubleBottom;
    bool WallLeft = DoubleLeft;

    // Wall finding

    if (!DoubleTop) {
        int Walls = 0;
        int WallLoops = (int) (SideRight / (double) pTilemap->TileSize()) -
                        (int) (SideLeft / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentX = SideLeft + pTilemap->TileSize() * i;

            TileType Type = pTilemap->GetTileWorld(CurrentX, SideTop)->GetType();
            if (Type == TileType::TILE_SOLID) Walls++;
        }
        WallTop = (bool) Walls;
    }
    if (!DoubleRight) {
        int Walls = 0;
        int WallLoops = (int) (SideBottom / (double) pTilemap->TileSize()) -
                        (int) (SideTop / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentY = SideTop + pTilemap->TileSize() * i;

            TileType Type = pTilemap->GetTileWorld(SideRight, CurrentY)->GetType();
            if (Type == TileType::TILE_SOLID) Walls++;
        }
        WallRight = (bool) Walls;
    }
    if (!DoubleBottom) {
        int Walls = 0;
        int WallLoops = (int) (SideRight / (double) pTilemap->TileSize()) -
                        (int) (SideLeft / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentX = SideLeft + pTilemap->TileSize() * i;

            TileType Type = pTilemap->GetTileWorld(CurrentX, SideBottom)->GetType();
            if (Type == TileType::TILE_SOLID) Walls++;
        }
        WallBottom = (bool) Walls;
    }
    if (!DoubleLeft) {
        int Walls = 0;
        int WallLoops = (int) (SideBottom / (double) pTilemap->TileSize()) -
                        (int) (SideTop / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentY = SideTop + pTilemap->TileSize() * i;

            TileType Type = pTilemap->GetTileWorld(SideLeft, CurrentY)->GetType();
            if (Type == TileType::TILE_SOLID) Walls++;
        }
        WallLeft = (bool) Walls;
    }

    // Snapping (1 Corner and closest axis)

    if (CornerTopLeft && !WallTop && !WallLeft) {
        double difx = SideLeft - pTilemap->TileLowFace(SideLeft);
        double dify = SideTop - pTilemap->TileLowFace(SideTop);

        if (difx > dify) WallLeft = true;
        else if (difx < dify) WallTop = true;
        else; // CORNER CASE
    }
    if (CornerTopRight && !WallTop && !WallRight) {
        double difx = pTilemap->TileHighFace(SideRight) - SideRight;
        double dify = SideTop - pTilemap->TileLowFace(SideTop);

        if (difx > dify) WallRight = true;
        else if (difx < dify) WallTop = true;
        else; // CORNER CASE
    }
    if (CornerBottomRight && !WallBottom && !WallRight) {
        double difx = pTilemap->TileHighFace(SideRight) - SideRight;
        double dify = pTilemap->TileHighFace(SideBottom) - SideBottom;

        if (difx > dify) WallRight = true;
        else if (difx < dify) WallBottom = true;
        else; // CORNER CASE
    }
    if (CornerBottomLeft && !WallBottom && !WallLeft) {
        double difx = SideLeft - pTilemap->TileLowFace(SideLeft);
        double dify = pTilemap->TileHighFace(SideBottom) - SideBottom;

        if (difx > dify) WallLeft = true;
        else if (difx < dify) WallBottom = true;
        else; // CORNER CASE
    }

    // Snapping (2 Corners or >1 Walls)

    if (WallTop) {
        m_y = pTilemap->TileHighFace(SideTop) + m_h2;
        m_yvel = 0.0;
    }
    if (WallRight) {
        m_x = pTilemap->TileLowFace(SideRight) - m_w2;
        m_xvel = 0.0;
    }
    m_Jump = WallBottom;
    if (WallBottom) {
        m_y = pTilemap->TileLowFace(SideBottom) - m_h2;
        m_yvel = 0.0;
    }
    if (WallLeft) {
        m_x = pTilemap->TileHighFace(SideLeft) + m_w2;
        m_xvel = 0.0;
    }
}

void CCharacter::Tick() {
    CClock* pClock = m_pGameworld->Window()->Clock();
    double DeltaTime = pClock->TimeElapsed();

    CInput* pInput = m_pGameworld->Window()->Input();
    bool Reset = pInput->GetKeyTap(SDL_SCANCODE_R);
    bool HeightUp = pInput->GetKey(SDL_SCANCODE_W);
    bool HeightDown = pInput->GetKey(SDL_SCANCODE_S);
    bool WidthUp = pInput->GetKey(SDL_SCANCODE_D);
    bool WidthDown = pInput->GetKey(SDL_SCANCODE_A);

    if (Reset) {
        m_pGameworld->TileMap()->FindTileWorld(TileType::TILE_SPAWNPOINT, &m_x, &m_y);
        m_lastx = m_x;
        m_lasty = m_y;
        m_xvel = 0;
        m_yvel = 0;
    }

    if (HeightUp != HeightDown) {
        if (HeightUp) Morph(m_w, m_h + 1);
        else Morph(m_w, m_h - 1);
    }
    if (WidthUp != WidthDown) {
        if (WidthUp) Morph(m_w + 1, m_h);
        else Morph(m_w - 1, m_h);
    }

    Movement();

    m_yvel += GRAVITY * DeltaTime;

    m_xvel *= pow(0.2, DeltaTime);
    m_yvel *= pow(0.2, DeltaTime);

    m_x += m_xvel * DeltaTime;
    m_y += m_yvel * DeltaTime;

    TileCollisions();
    m_lastx = m_x;
    m_lasty = m_y;
}

void CCharacter::Draw() {
    CDrawing* pDrawing = m_pGameworld->Window()->Drawing();

    SDL_Rect Rect = GetRect();
    pDrawing->SetColor(255, 255, 0, 255);
    pDrawing->FillRect(GetRect(), true);
}
