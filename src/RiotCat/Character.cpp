#include "Character.h"
#include "vec2.h"
#include <vector>

CCharacter::CCharacter(CGameWorld* pGameworld, double X, double Y) {
    m_pGameworld = pGameworld;
    m_x = X;
    m_y = Y;
    m_w = 20;
    m_h = 30;
    m_xvel = 0.0;
    m_yvel = 0.0;
    m_Jump = false;

    CInput* pInput = m_pGameworld->Window()->Input();
    pInput->AddKey(SDL_SCANCODE_W);
    pInput->AddKey(SDL_SCANCODE_D);
    pInput->AddKey(SDL_SCANCODE_S);
    pInput->AddKey(SDL_SCANCODE_A);
}

CCharacter::~CCharacter() {

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

void CCharacter::Tick() {
    CClock* pClock = m_pGameworld->Window()->Clock();
    double DeltaTime = pClock->TimeElapsed();

    Movement();

    m_yvel += GRAVITY * DeltaTime;

    m_xvel *= pow(0.2, DeltaTime);
    m_yvel *= pow(0.2, DeltaTime);

    m_x += m_xvel * DeltaTime;
    m_y += m_yvel * DeltaTime;

    //

    CTileMap* pTilemap = m_pGameworld->TileMap();


    double DLeft = m_x - m_w/2;
    double DRight = m_x + m_w/2;
    double DTop = m_y - m_h/2;
    double DBottom = m_y + m_h/2;

    TileType TopLeft = pTilemap->GetTileWorld(vec2d(DLeft, DTop))->GetType();
    TileType TopRight = pTilemap->GetTileWorld(vec2d(DRight, DTop))->GetType();
    TileType BottomLeft = pTilemap->GetTileWorld(vec2d(DLeft, DBottom))->GetType();
    TileType BottomRight = pTilemap->GetTileWorld(vec2d(DRight, DBottom))->GetType();

    bool Left = TopLeft == TILE_SOLID && BottomLeft == TILE_SOLID;
    bool Right = TopRight == TILE_SOLID && BottomRight == TILE_SOLID;
    bool Top = TopLeft == TILE_SOLID && TopRight == TILE_SOLID;
    bool Bottom = BottomLeft == TILE_SOLID && BottomRight == TILE_SOLID;

    if (Bottom != Top) {
        if (Bottom) {
            int tiley = (int)(DBottom / (double)pTilemap->TileSize());
            double y = tiley * pTilemap->TileSize();
            m_y = y - m_h / 2;
            m_yvel = 0.0;
            m_Jump = true;
        } else {
            int tiley = (int)(DTop / (double)pTilemap->TileSize()) + 1;
            double y = tiley * pTilemap->TileSize();
            m_y = y + m_h / 2;
            m_yvel = 0.0;
        }
    }
    if (Right != Left) {
        if (Right) {
            int tilex = (int)(DRight / (double)pTilemap->TileSize());
            double x = tilex * pTilemap->TileSize();
            m_x = x - m_w / 2;
            m_xvel = 0.0;
        } else {
            int tilex = (int)(DLeft / (double)pTilemap->TileSize()) + 1;
            double x = tilex * pTilemap->TileSize();
            m_x = x + m_w / 2;
            m_xvel = 0.0;
        }
    }

    // :E

    WallCollision();
}

void CCharacter::Draw() {
    CDrawing* pDrawing = m_pGameworld->Window()->Drawing();

    SDL_Rect Rect = GetRect();
    pDrawing->SetColor(255, 255, 255, 255);
    pDrawing->FillRect(&Rect);
}