#include "Clock.h"

CClock::CClock(double frequency)
{
    m_Frequency = frequency;
    m_PeriodDelay = 1.0 / frequency;
}

void CClock::Begin()
{
    m_Begin = chrono::steady_clock::now();
}

void CClock::End()
{
    m_End = chrono::steady_clock::now();
    m_TimeElapsed = (double)(chrono::duration_cast<chrono::nanoseconds>(m_End - m_Begin).count()) * 1e-9;
}