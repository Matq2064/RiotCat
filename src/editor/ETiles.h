#ifndef RIOTCAT_ETILES_H
#define RIOTCAT_ETILES_H

#include "../Tiles.h"
#include <map>
using namespace std;

class CETiles : public CTiles {
private:
    enum TileInput {
        LCLICK,
        MCLICK,
        RCLICK,
        NUM_INP
    };
    map<int, int> m_mInputMapping;
    bool m_aInput[NUM_INP], m_aLastInput[NUM_INP];
    int m_mx, m_my;

public:
    CETiles();
    CETiles(int width, int height);

    void Input(SDL_Event& Event) override; // dis not worrk fix
    void Tick();
};

#endif //RIOTCAT_ETILES_H
