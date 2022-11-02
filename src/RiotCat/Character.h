#ifndef RIOTCATE_CHARACTER_H
#define RIOTCATE_CHARACTER_H

#include "Rect.h"
#include "Gameworld.h"
#include <cmath>
#include <map>
using namespace std;

class CCharacter : public CHandleRect {
private:
    enum Controls {
        CONTROL_JUMP,
        CONTROL_RIGHT,
        CONTROL_DOWN,
        CONTROL_LEFT,
        CONTROL_RESET,
        CONTROL_MORPH_VERTICAL,
        CONTROL_MORPH_HORIZONTAL,
        NUM_CONTROLS
    };

    enum CollideSide {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    CGameWorld* m_pGameworld;
    double m_lastx, m_lasty, m_xvel, m_yvel;
    bool m_Jump;
    bool m_aControls[Controls::NUM_CONTROLS];
    bool m_aColliding[4];

    void Initialize(CGameWorld* pGameworld);
    void Controls();
    void Morphing();
    void Movement();
    void WallCollision();
    void TileCollision();
    void TileCollisions();

public:
    CCharacter(CGameWorld* pGameworld);
    CCharacter(CGameWorld* pGameworld, double x, double y);
    ~CCharacter();

    void Tick();
    void Draw();
};

#endif //RIOTCATE_CHARACTER_H
