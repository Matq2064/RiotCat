#ifndef RIOTCAT_INPUT_H
#define RIOTCAT_INPUT_H

#include <SDL.h>

class CInput
{
private:
    bool m_Quit = false;

public:
    CInput();

    void Tick();
    bool GetQuit() const { return m_Quit; }
};

#endif //RIOTCAT_INPUT_H
