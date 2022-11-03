#include "Character.h"

CCharacter::CCharacter(CGameWorld* pGameworld)
        : CHandleRect(0, 0, 50.0, 50.0) {
    pGameworld->SpawnCoordinates(&m_x, &m_y);
    Initialize(pGameworld);
}

CCharacter::CCharacter(CGameWorld* pGameworld, double x, double y)
        : CHandleRect(x, y, 50.0, 50.0) {
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
    m_pTexture = m_pGameworld->Window()->Drawing()->GetTexture("butter");

    for (int i = 0; i < sizeof(m_aControls); i++)
        m_aControls[i] = false;

    for (int i = 0; i < sizeof(m_aColliding); i++)
        m_aColliding[i] = false;

    CInput* pInput = m_pGameworld->Window()->Input();
    pInput->AddKey(SDL_SCANCODE_W);
    pInput->AddKey(SDL_SCANCODE_D);
    pInput->AddKey(SDL_SCANCODE_S);
    pInput->AddKey(SDL_SCANCODE_A);
    pInput->AddKey(SDL_SCANCODE_R);
    pInput->AddKey(SDL_SCANCODE_UP);
    pInput->AddKey(SDL_SCANCODE_DOWN);
}
void CCharacter::Controls() {
    CInput* pInput = m_pGameworld->Window()->Input();
    m_aControls[CONTROL_JUMP] = pInput->GetKeyTap(SDL_SCANCODE_W);
    m_aControls[CONTROL_RIGHT] = pInput->GetKey(SDL_SCANCODE_D);
    m_aControls[CONTROL_DOWN] = pInput->GetKey(SDL_SCANCODE_S);
    m_aControls[LEFT] = pInput->GetKey(SDL_SCANCODE_A);
    m_aControls[CONTROL_RESET] = pInput->GetKeyTap(SDL_SCANCODE_R);
    m_aControls[CONTROL_MORPH_VERTICAL] = pInput->GetKey(SDL_SCANCODE_UP);
    m_aControls[CONTROL_MORPH_HORIZONTAL] = pInput->GetKey(SDL_SCANCODE_DOWN);
}

void CCharacter::Morphing() {
    if (m_aControls[CONTROL_MORPH_HORIZONTAL] != m_aControls[CONTROL_MORPH_VERTICAL]) {
        if (m_aControls[CONTROL_MORPH_VERTICAL] && !(m_aControls[UP] && m_aControls[DOWN])) {
            if (m_w > 10.0) Morph(m_w-1, m_h+1);
        }
        else if (!(m_aControls[LEFT] && m_aControls[RIGHT])) {
            if(m_h > 10.0) Morph(m_w+1, m_h-1);
        }
    }
}

void CCharacter::Movement() {
    CInput* pInput = m_pGameworld->Window()->Input();
    CClock* pClock = m_pGameworld->Window()->Clock();
    double DeltaTime = pClock->TimeElapsed();

    double SomeAccel = 1500;
    double Accel = SomeAccel * DeltaTime * (m_Jump ? 1.0 : 0.5);
    if (m_aControls[CONTROL_JUMP] && m_Jump) {
        m_yvel = -1000;
        m_Jump = false;
    }
    if (m_aControls[CONTROL_DOWN]) m_yvel += Accel;

    if (m_aControls[LEFT] != m_aControls[CONTROL_RIGHT]) {
        if (m_aControls[LEFT]) m_xvel -= Accel;
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

    bool Finish = pTilemap->GetTileWorld(SideLeft, SideTop)->GetType() == TileType::TILE_FINISH ||
                  pTilemap->GetTileWorld(SideRight, SideTop)->GetType() == TileType::TILE_FINISH ||
                  pTilemap->GetTileWorld(SideLeft, SideBottom)->GetType() == TileType::TILE_FINISH ||
                  pTilemap->GetTileWorld(SideRight, SideBottom)->GetType() == TileType::TILE_FINISH;

    if (Finish)
        m_pGameworld->SetFinished(true);

    if (Deth) {
        m_pGameworld->TileMap()->FindTileWorld(TileType::TILE_SPAWNPOINT, &m_x, &m_y);
        m_lastx = m_x;
        m_lasty = m_y;
        return;
    }

    bool CornerTopLeft = pTilemap->GetTileWorld(SideLeft, SideTop)->Collides();
    bool CornerTopRight = pTilemap->GetTileWorld(SideRight, SideTop)->Collides();
    bool CornerBottomLeft = pTilemap->GetTileWorld(SideLeft, SideBottom)->Collides();
    bool CornerBottomRight = pTilemap->GetTileWorld(SideRight, SideBottom)->Collides();

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

            if (pTilemap->GetTileWorld(CurrentX, SideTop)->Collides()) Walls++;
        }
        WallTop = (bool) Walls;
    }
    if (!DoubleRight) {
        int Walls = 0;
        int WallLoops = (int) (SideBottom / (double) pTilemap->TileSize()) -
                        (int) (SideTop / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentY = SideTop + pTilemap->TileSize() * i;

            if (pTilemap->GetTileWorld(SideRight, CurrentY)->Collides()) Walls++;
        }
        WallRight = (bool) Walls;
    }
    if (!DoubleBottom) {
        int Walls = 0;
        int WallLoops = (int) (SideRight / (double) pTilemap->TileSize()) -
                        (int) (SideLeft / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentX = SideLeft + pTilemap->TileSize() * i;

            if (pTilemap->GetTileWorld(CurrentX, SideBottom)->Collides()) Walls++;
        }
        WallBottom = (bool) Walls;
    }
    if (!DoubleLeft) {
        int Walls = 0;
        int WallLoops = (int) (SideBottom / (double) pTilemap->TileSize()) -
                        (int) (SideTop / (double) pTilemap->TileSize()) - 1;
        for (int i = 1; i <= WallLoops; i++) {
            double CurrentY = SideTop + pTilemap->TileSize() * i;

            if (pTilemap->GetTileWorld(SideLeft, CurrentY)->Collides()) Walls++;
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
        m_aColliding[UP] = true;
        m_y = pTilemap->TileHighFace(SideTop) + m_h2;
        m_yvel = 0.0;
    }
    if (WallRight) {
        m_aColliding[RIGHT] = true;
        m_x = pTilemap->TileLowFace(SideRight) - m_w2;
        m_xvel = 0.0;
    }
    m_Jump = WallBottom;
    if (WallBottom) {
        m_aColliding[DOWN] = true;
        m_y = pTilemap->TileLowFace(SideBottom) - m_h2;
        m_yvel = 0.0;
    }
    if (WallLeft) {
        m_aColliding[LEFT] = true;
        m_x = pTilemap->TileHighFace(SideLeft) + m_w2;
        m_xvel = 0.0;
    }
}

void CCharacter::Tick() {
    if(m_pGameworld->Finished())
        return;

    CClock* pClock = m_pGameworld->Window()->Clock();
    double DeltaTime = pClock->TimeElapsed();

    Controls();
    Morphing();

    if (m_aControls[CONTROL_RESET]) {
        m_pGameworld->TileMap()->FindTileWorld(TileType::TILE_SPAWNPOINT, &m_x, &m_y);
        m_lastx = m_x;
        m_lasty = m_y;
        m_xvel = 0;
        m_yvel = 0;
    }

    Movement();

    m_xvel *= m_Jump && m_aControls[CONTROL_DOWN] ? 0.9 : 1.0;
    m_yvel += GRAVITY * DeltaTime;

    m_xvel *= pow(0.2, DeltaTime);
    m_yvel *= pow(0.2, DeltaTime);

    m_x += m_xvel * DeltaTime;
    m_y += m_yvel * DeltaTime;

    for (int i = 0; i < sizeof(m_aColliding); i++)
        m_aColliding[i] = false;

    TileCollisions();

    m_lastx = m_x;
    m_lasty = m_y;
}

void CCharacter::Draw() {
    CDrawing* pDrawing = m_pGameworld->Window()->Drawing();

    SDL_Rect Rect = GetRect();
    pDrawing->RenderCopy(m_pTexture, nullptr, &Rect, true);
    // pDrawing->SetColor(255, 255, 0, 255);
    // pDrawing->FillRect(GetRect(), true);
}
