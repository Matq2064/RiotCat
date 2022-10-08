#include "ETiles.h"

CETiles::CETiles()
    : CTiles() {

}

CETiles::CETiles(int width, int height)
    : CTiles(width, height) {
    m_mInputMapping[SDL_BUTTON_LEFT] = LCLICK;
    m_mInputMapping[SDL_BUTTON_MIDDLE] = MCLICK;
    m_mInputMapping[SDL_BUTTON_RIGHT] = RCLICK;

    memset(m_aInput, 0, sizeof(m_aInput));
    memset(m_aLastInput, 0, sizeof(m_aLastInput));
}

void CETiles::Input(SDL_Event& Event) {
    CTiles::Input(Event);

    if (Event.type != SDL_MOUSEBUTTONDOWN && Event.type != SDL_MOUSEBUTTONUP)
        return;

    int Button = Event.button.button;
    if (m_mInputMapping.find(Button) == m_mInputMapping.end())
        return;

    int Index = m_mInputMapping[Button];
    bool State = Event.type == SDL_MOUSEBUTTONDOWN;
    m_aInput[Index] = State;
}

void CETiles::Tick() {
    SDL_GetMouseState(&m_mx, &m_my);
    if (m_aInput[RCLICK]) {
        int x = m_mx / m_TileSize;
        int y = m_my / m_TileSize;

        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            int ID = y * m_width + x;
            m_aTiles[ID] = TILE_SOMETHING;
        }
    }

    memcpy(&m_aLastInput, &m_aInput, sizeof(m_aLastInput));
}