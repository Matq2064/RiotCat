#include "Input.h"
#include <algorithm>

CInput::CInput() {

}

void CInput::Tick() {
    m_mLastInputKeyMapping.clear();
    m_mLastInputKeyMapping.insert(m_mInputKeyMapping.begin(), m_mInputKeyMapping.end());
    m_mLastInputButtonMapping.clear();
    m_mLastInputButtonMapping.insert(m_mInputButtonMapping.begin(), m_mInputButtonMapping.end());

    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        switch (Event.type) {
            case SDL_QUIT: {
                m_Quit = true;
            } break;
            case SDL_KEYDOWN: {
                int Scancode = Event.key.keysym.scancode;
                if (m_mInputKeyMapping.find(Scancode) != m_mInputKeyMapping.end())
                    m_mInputKeyMapping[Scancode] = true;
            } break;
            case SDL_KEYUP: {
                int Scancode = Event.key.keysym.scancode;
                if (m_mInputKeyMapping.find(Scancode) != m_mInputKeyMapping.end())
                    m_mInputKeyMapping[Scancode] = false;
            } break;
            case SDL_MOUSEBUTTONDOWN: {
                int Button = Event.button.button;
                bool Found = m_mInputButtonMapping.find(Button) != m_mInputButtonMapping.end();
                if (Found) m_mInputButtonMapping[Button] = true;
            } break;
            case SDL_MOUSEBUTTONUP: {
                int Button = Event.button.button;
                if (m_mInputButtonMapping.find(Button) != m_mInputButtonMapping.end())
                    m_mInputButtonMapping[Button] = false;
            } break;
        }
    }
}


void CInput::AddKey(int sdl_mapping) {
    if (m_mInputKeyMapping.find(sdl_mapping) == m_mInputKeyMapping.end())
        m_mInputKeyMapping[sdl_mapping] = false;
}

bool CInput::GetKey(int sdl_mapping) {
    auto Iterator = m_mInputKeyMapping.find(sdl_mapping);
    if (Iterator == m_mInputKeyMapping.end()) {
        AddKey(sdl_mapping);
        return false;
    }

    return Iterator->second;
}

bool CInput::GetLastKey(int sdl_mapping) {
    auto Iterator = m_mLastInputKeyMapping.find(sdl_mapping);
    if (Iterator == m_mLastInputKeyMapping.end()) {
        AddKey(sdl_mapping);
        return false;
    }

    return Iterator->second;
}

bool CInput::GetKeyTap(int sdl_mapping) {
    return GetKey(sdl_mapping) && !GetLastKey(sdl_mapping);
}

void CInput::AddButton(int sdl_mapping) {
    if (m_mInputButtonMapping.find(sdl_mapping) == m_mInputButtonMapping.end())
        m_mInputButtonMapping[sdl_mapping] = false;
}

bool CInput::GetButton(int sdl_mapping) {
    auto Iterator = m_mInputButtonMapping.find(sdl_mapping);
    if (Iterator == m_mInputButtonMapping.end()) {
        AddButton(sdl_mapping);
        return false;
    }

    return Iterator->second;
}

bool CInput::GetLastButton(int sdl_mapping) {
    auto Iterator = m_mLastInputButtonMapping.find(sdl_mapping);
    if (Iterator == m_mLastInputButtonMapping.end()) {
        AddButton(sdl_mapping);
        return false;
    }

    return Iterator->second;
}

bool CInput::GetButtonTap(int sdl_mapping) {
    return GetButton(sdl_mapping) && !GetLastButton(sdl_mapping);
}
