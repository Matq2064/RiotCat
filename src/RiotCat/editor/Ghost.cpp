#include "Ghost.h"

CGhost::CGhost(CInput* pInput, double startx, double starty)
    : CHandleRect(startx, starty, 0, 0) {
    m_pInput = pInput;
    pInput->AddKey(SDL_SCANCODE_W);
    pInput->AddKey(SDL_SCANCODE_A);
    pInput->AddKey(SDL_SCANCODE_S);
    pInput->AddKey(SDL_SCANCODE_D);
}

void CGhost::Tick() {
    bool Up = m_pInput->GetKey(SDL_SCANCODE_W);
    bool Right = m_pInput->GetKey(SDL_SCANCODE_D);
    bool Down = m_pInput->GetKey(SDL_SCANCODE_S);
    bool Left = m_pInput->GetKey(SDL_SCANCODE_A);
    bool SpeedUp = m_pInput->GetKey(SDL_SCANCODE_LSHIFT);
    double Speed = SpeedUp ? 15.0 : 5.0;

    if (Right != Left) {
        if (Right) m_x += Speed;
        else m_x -= Speed;
    }

    if (Up != Down) {
        if (Up) m_y -= Speed;
        else m_y += Speed;
    }
}
