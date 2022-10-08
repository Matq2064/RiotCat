#define SDL_MAIN_HANDLED

#include "Window.h"
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

int WIDTH = 900;
int HEIGHT = 700;
CWindow* pWindow;

class CTiles {
private:
    int m_TileSize = 32.f;
    int m_width, m_height;
    int* m_aTiles;

    enum TileEnum {
        TILE_NONE,
        TILE_SOMETHING,
        TILE_DETH,
        NUM_TILES,
        DEFAULT = TILE_NONE,
    };

public:
    CTiles(int width, int height) {
        m_width = width;
        m_height = height;

        int Area_ = Area();
        m_aTiles = new int[Area_];
        for (int i = 0; i < Area_; i++)
            m_aTiles[i] = rand() % 3;

    }
    ~CTiles() {
        delete[] m_aTiles;
    }

    int Width() const { return m_width; }
    int Height() const { return m_height; }
    int Area() const { return Width() * Height(); }
    void Draw(CDrawing* pDrawing) {
        for (int i = 0; i < Area(); i++) {
            int TileX = i % Width();
            int TileY = i / Height();

            int TileID = m_aTiles[i];
            switch (TileID) {
                case TILE_NONE:
                    continue;
                case TILE_SOMETHING: {
                    pDrawing->SetColor(255, 255, 255, 255);
                } break;
                case TILE_DETH: {
                    pDrawing->SetColor(255, 0, 0, 255);
                } break;
            }

            SDL_Rect Rect;
            Rect.x = TileX * m_TileSize;
            Rect.y = TileY * m_TileSize;
            Rect.w = m_TileSize;
            Rect.h = m_TileSize;
            pDrawing->FillRect(&Rect);
        }
    }
} *pTiles;

class CCharacter : public CHandleInput {
private:
    double m_x, m_y, m_w, m_h, m_xvel, m_yvel;
    bool m_Jump;

    enum {
        INP_UP,
        INP_RIGHT,
        INP_DOWN,
        INP_LEFT,
        NUM_INP
    };

    map<int, int> m_mInputMapping;
    bool m_aInput[NUM_INP], m_aLastInput[NUM_INP];

public:
    CCharacter(double X, double Y) {
        m_x = X;
        m_y = Y;
        m_w = 50;
        m_h = 70;
        m_xvel = 0.0;
        m_yvel = 0.0;
        m_Jump = false;

        m_mInputMapping[SDL_SCANCODE_W] = INP_UP;
        m_mInputMapping[SDL_SCANCODE_D] = INP_RIGHT;
        m_mInputMapping[SDL_SCANCODE_S] = INP_DOWN;
        m_mInputMapping[SDL_SCANCODE_A] = INP_LEFT;

        for (int i = 0; i < NUM_INP; i++) {
            m_aInput[i] = false;
            m_aLastInput[i] = false;
        }
    }

    void Input(SDL_Event& Event) override {
        if (Event.type != SDL_KEYDOWN && Event.type != SDL_KEYUP)
            return;

        int Scancode = Event.key.keysym.scancode;
        if (m_mInputMapping.find(Scancode) == m_mInputMapping.end())
            return;
        int Index = m_mInputMapping[Scancode];
        bool State = Event.type == SDL_KEYDOWN;
        m_aInput[Index] = State;
    }
    void Tick(double time_elapsed) {
        bool Jump = m_aInput[INP_UP] && !m_aLastInput[INP_UP];
        bool Right = m_aInput[INP_RIGHT];
        bool Down = m_aInput[INP_DOWN];
        bool Left = m_aInput[INP_LEFT];

        double SomeAccel = 2500;
        double Accel = SomeAccel * time_elapsed;
        if (Jump && m_Jump) {
            m_yvel = -1000;
            m_Jump = false;
        }
        if (Down) m_yvel += Accel;

        if (Left != Right) {
            if (Left) m_xvel -= Accel;
            else m_xvel += Accel;
        }

        m_yvel += 1500 * time_elapsed;

        m_xvel *= pow(0.2, time_elapsed);
        m_yvel *= pow(0.2, time_elapsed);

        m_x += m_xvel * time_elapsed;
        m_y += m_yvel * time_elapsed;

        bool ColLeft = m_x - m_w/2 < 0.0;
        bool ColRight = m_x + m_w/2 > WIDTH;
        bool ColUp = m_y - m_h/2 < 0.0;
        bool ColDown = m_y + m_h/2 > HEIGHT;

        if (ColLeft || ColRight) {
            m_xvel = 0.0;
            if (ColLeft) m_x = m_w/2;
            else m_x = WIDTH - m_w/2;
        }
        if (ColUp || ColDown) {
            m_yvel = 0.0;
            if (ColUp) m_y = m_h/2;
            else {
                m_y = HEIGHT - m_h/2;
                m_Jump = true;
            }
        }

        memcpy(&m_aLastInput, &m_aInput, sizeof(m_aInput));
    }
    void Draw(CDrawing* pDrawing) {
        SDL_Rect Rect;
        Rect.x = (int)(m_x - m_w/2);
        Rect.y = (int)(m_y - m_h/2);
        Rect.w = (int)(m_w);
        Rect.h = (int)(m_h);
        pDrawing->SetColor(255, 255, 255, 255);
        pDrawing->FillRect(&Rect);
    }
} *pCharacter;

int main() {
    pWindow = new CWindow("RiotCat", WIDTH, HEIGHT);
    if (!pWindow->Initialized())
        return -1;

    pTiles = new CTiles(20, 20);
    pCharacter = new CCharacter(300, 300);
    pWindow->Input()->AddObject(pCharacter);

    CClock* pClock = pWindow->Clock();
    CInput* pInput = pWindow->Input();
    CDrawing* pDrawing = pWindow->Drawing();
    while (true)
    {
        pClock->Begin();

        pInput->Tick();
        if (pInput->GetQuit())
            break;

        pCharacter->Tick(pClock->TimeElapsed());

        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();
        pTiles->Draw(pDrawing);
        pCharacter->Draw(pDrawing);
        pDrawing->Present();

        do { pClock->End(); }
        while (pClock->TimeElapsed() < 1.0 / 75.0);
    }

    delete pCharacter;
    delete pTiles;
    delete pWindow;
    return 0;
}
