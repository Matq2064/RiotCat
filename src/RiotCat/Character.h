#ifndef RIOTCATE_CHARACTER_H
#define RIOTCATE_CHARACTER_H

#include "Rect.h"
#include "Window.h"
#include <cmath>
#include <map>
using namespace std;

class CCharacter : public CHandleInput, CHandleRect {
private:
    CWindow* m_pWindow;
    double m_xvel, m_yvel;
    bool m_Jump;

    enum CharacterInput {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        NUM_INP
    };

    map<int, int> m_mInputMapping;
    bool m_aInput[NUM_INP], m_aLastInput[NUM_INP];

public:
    CCharacter(CWindow* pWindow, double X, double Y);
    ~CCharacter();

    void Input(SDL_Event& Event) override;
    void Tick(double time_elapsed);
    void Draw();
};

#endif //RIOTCATE_CHARACTER_H
