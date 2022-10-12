#ifndef RIOTCATE_CHARACTER_H
#define RIOTCATE_CHARACTER_H

#include "Rect.h"
#include "Window.h"
#include <cmath>
#include <map>
using namespace std;

class CCharacter : public CHandleRect {
private:
    CWindow* m_pWindow;
    double m_xvel, m_yvel;
    bool m_Jump;

public:
    CCharacter(CWindow* pWindow, double X, double Y);
    ~CCharacter();

    void Tick(double time_elapsed);
    void Draw();
};

#endif //RIOTCATE_CHARACTER_H
