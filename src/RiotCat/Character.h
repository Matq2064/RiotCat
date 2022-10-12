#ifndef RIOTCATE_CHARACTER_H
#define RIOTCATE_CHARACTER_H

#include "Rect.h"
#include "Gameworld.h"
#include <cmath>
#include <map>
using namespace std;

class CCharacter : public CHandleRect {
private:
    CGameWorld* m_pGameworld;
    double m_xvel, m_yvel;
    bool m_Jump;

    void Movement();
    void WallCollision();

public:
    CCharacter(CGameWorld* pGameworld, double X, double Y);
    ~CCharacter();

    void Tick();
    void Draw();
};

#endif //RIOTCATE_CHARACTER_H
