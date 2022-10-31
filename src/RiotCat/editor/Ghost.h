#ifndef RIOTCAT_GHOST_H
#define RIOTCAT_GHOST_H

#include "../Input.h"
#include "../Rect.h"

class CGhost : public CHandleRect {
private:
    CInput* m_pInput;

public:
    CGhost(CInput* pInput, double startx, double starty);

    void Tick();
};

#endif //RIOTCAT_GHOST_H
