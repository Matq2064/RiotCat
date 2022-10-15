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
    double m_lastx, m_lasty, m_xvel, m_yvel;
    bool m_Jump;

    void Initialize(CGameWorld* pGameworld);
    void Movement();
    void WallCollision();
    bool TileCollision();

public:
    CCharacter(CGameWorld* pGameworld);
    CCharacter(CGameWorld* pGameworld, double x, double y);
    ~CCharacter();

    void Tick();
    void Draw();
};

#endif //RIOTCATE_CHARACTER_H
