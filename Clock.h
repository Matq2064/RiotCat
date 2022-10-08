#ifndef RIOTCAT_CLOCK_H
#define RIOTCAT_CLOCK_H

#include <chrono>

using namespace std;

class CClock
{
private:
    double m_Frequency = -1.0;
    double m_TimeElapsed = 0.0;
    double m_PeriodDelay = 0.0;
    chrono::steady_clock::time_point m_Begin, m_End;

public:
    CClock(double frequency);

    void Begin();
    void End();
    double TimeElapsed() const { return m_TimeElapsed; }
};

#endif //RIOTCAT_CLOCK_H
