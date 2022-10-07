#define SDL_MAIN_HANDLED

#include "Window.h"
using namespace std;

int main() {
    CWindow Window("RiotCat", 500, 500);
    if (!Window.Initialized())
        return -1;

    CClock* pClock = Window.Clock();
    while (true)
    {
        pClock->Begin();

        CInput* pInput = Window.Input();
        pInput->Tick();
        if (pInput->GetQuit())
            break;

        CDrawing* pDrawing = Window.Drawing();
        pDrawing->SetColor(0, 0, 0, 255);
        pDrawing->Clear();

        pDrawing->Present();

        pClock->End(true);
    }

    return 0;
}
