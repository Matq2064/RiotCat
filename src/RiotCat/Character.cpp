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

    CInput* pInput = m_pWindow->Input();
    pInput->AddKey(SDL_SCANCODE_W);
    pInput->AddKey(SDL_SCANCODE_D);
    pInput->AddKey(SDL_SCANCODE_S);
    pInput->AddKey(SDL_SCANCODE_A);
}

CCharacter::~CCharacter() {

}

void CCharacter::Tick(double time_elapsed) {
    CInput* pInput = m_pWindow->Input();

    bool Jump = pInput->GetKeyTap(SDL_SCANCODE_W);
    bool Right = pInput->GetKey(SDL_SCANCODE_D);
    bool Down = pInput->GetKey(SDL_SCANCODE_S);
    bool Left = pInput->GetKey(SDL_SCANCODE_A);

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
}

void CCharacter::Draw() {
    CDrawing* pDrawing = m_pWindow->Drawing();

    SDL_Rect Rect = GetRect();
    pDrawing->SetColor(255, 255, 255, 255);
    pDrawing->FillRect(&Rect);
}