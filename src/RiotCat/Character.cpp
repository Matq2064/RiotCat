#include "Character.h"

CCharacter::CCharacter(CWindow* pWindow, double X, double Y) {
    m_pWindow = pWindow;
    m_x = X;
    m_y = Y;
    m_w = 50;
    m_h = 70;
    m_xvel = 0.0;
    m_yvel = 0.0;
    m_Jump = false;

    m_mInputMapping[SDL_SCANCODE_W] = UP;
    m_mInputMapping[SDL_SCANCODE_D] = RIGHT;
    m_mInputMapping[SDL_SCANCODE_S] = DOWN;
    m_mInputMapping[SDL_SCANCODE_A] = LEFT;

    for (int i = 0; i < NUM_INP; i++) {
        m_aInput[i] = false;
        m_aLastInput[i] = false;
    }

    m_pWindow->Input()->AddObject(this);
}

CCharacter::~CCharacter() {
    m_pWindow->Input()->RemoveObject(this);
}

void CCharacter::Input(SDL_Event& Event) {
    if (Event.type != SDL_KEYDOWN && Event.type != SDL_KEYUP)
        return;

    int Scancode = Event.key.keysym.scancode;
    if (m_mInputMapping.find(Scancode) == m_mInputMapping.end())
        return;
    int Index = m_mInputMapping[Scancode];
    bool State = Event.type == SDL_KEYDOWN;
    m_aInput[Index] = State;
}

void CCharacter::Tick(double time_elapsed) {
    bool Jump = m_aInput[UP] && !m_aLastInput[UP];
    bool Right = m_aInput[RIGHT];
    bool Down = m_aInput[DOWN];
    bool Left = m_aInput[LEFT];

    double SomeAccel = 2500;
    double Accel = SomeAccel * time_elapsed;
    if (Jump && m_Jump) {
        m_yvel = -1000;
        m_Jump = false;
    }
    if (Down) m_yvel += Accel;

    if (Left != Right) {
        if (Left) m_xvel -= Accel;
        else m_xvel += Accel;
    }

    m_yvel += 1500 * time_elapsed;

    m_xvel *= pow(0.2, time_elapsed);
    m_yvel *= pow(0.2, time_elapsed);

    m_x += m_xvel * time_elapsed;
    m_y += m_yvel * time_elapsed;

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

    memcpy(&m_aLastInput, &m_aInput, sizeof(m_aInput));
}

void CCharacter::Draw() {
    CDrawing* pDrawing = m_pWindow->Drawing();

    SDL_Rect Rect = GetRect();
    pDrawing->SetColor(255, 255, 255, 255);
    pDrawing->FillRect(&Rect);
}