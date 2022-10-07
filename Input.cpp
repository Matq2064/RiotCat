#include "Input.h"

CInput::CInput()
{

}

void CInput::Tick()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                m_Quit = true;
            } break;
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    m_Quit = true;
            } break;
        }
    }
}