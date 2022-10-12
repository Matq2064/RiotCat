#ifndef RIOTCAT_INPUT_H
#define RIOTCAT_INPUT_H

#include <SDL.h>
#include <map>
using namespace std;

class CInput
{
private:
    map<int, bool> m_mInputKeyMapping;
    map<int, bool> m_mLastInputKeyMapping;
    map<int, bool> m_mInputButtonMapping;
    map<int, bool> m_mLastInputButtonMapping;
    bool m_Quit = false;

public:
    CInput();

    void Tick();
    bool GetQuit() const { return m_Quit; }

    void AddKey(int sdl_index);
    bool GetKey(int sdl_index);
    bool GetLastKey(int sdl_index);
    bool GetKeyTap(int sdl_index);
    void AddButton(int sdl_index);
    bool GetButton(int sdl_index);
    bool GetLastButton(int sdl_index);
    bool GetButtonTap(int sdl_index);

};

#endif //RIOTCAT_INPUT_H
