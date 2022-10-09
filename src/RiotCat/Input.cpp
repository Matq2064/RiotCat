#include "Input.h"
#include <algorithm>

CInput::CInput() {

}

void CInput::Tick() {
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
            case SDL_QUIT: {
                m_Quit = true;
            } break;
            case SDL_KEYDOWN: {
                if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    m_Quit = true;
            } break;
        }

        for (CHandleInput* pObject : m_vpObjects)
            pObject->Input(Event);
    }
}

void CInput::AddObject(CHandleInput* pObject) {
    m_vpObjects.push_back(pObject);
}

void CInput::RemoveObject(CHandleInput *pObject) {
    m_vpObjects.erase(remove(m_vpObjects.begin(), m_vpObjects.end(), pObject), m_vpObjects.end());
}
