#ifndef RIOTCATE_CHARACTER_H
#define RIOTCATE_CHARACTER_H

#include "Rect.h"
#include "Input.h"
#include "Drawing.h"
#include <cmath>
#include <map>
using namespace std;

class CCharacter : public CHandleInput, CHandleRect {
private:
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
    CCharacter(double X, double Y);

    void Input(SDL_Event& Event) override;
    void Tick(double time_elapsed);
    void Draw(CDrawing* pDrawing);
};

#endif //RIOTCATE_CHARACTER_H
