#ifndef RIOTCAT_INPUT_H
#define RIOTCAT_INPUT_H

#include <SDL.h>
#include <vector>
using namespace std;

class CHandleInput {
public:
    virtual void Input(SDL_Event& Event) {};

};

class CInput
{
private:
    vector<CHandleInput*> m_vpObjects;
    bool m_Quit = false;

public:
    CInput();

    void Tick();
    void AddObject(CHandleInput* pObject);
    void RemoveObject(CHandleInput* pObject);
    bool GetQuit() const { return m_Quit; }
};

#endif //RIOTCAT_INPUT_H
