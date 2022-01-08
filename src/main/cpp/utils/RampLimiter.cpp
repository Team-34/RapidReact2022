#include "utils/RampLimiter.h"

RampLimiter::RampLimiter(double rate_limit, double initial_value)
    : m_rate_limit(rate_limit)
    , m_prev_value(initial_value)
    , m_prev_time(frc::Timer::GetFPGATimestamp())
{
}

double RampLimiter::Calculate(double input)
{
    double current_time{ frc::Timer::GetFPGATimestamp() };
    double elapsed_time = current_time - m_prev_time;
    m_prev_value += std::clamp(input - m_prev_value, -m_rate_limit * elapsed_time, m_rate_limit * elapsed_time);
    m_prev_time = current_time;
    return m_prev_value;
}

void RampLimiter::Reset(double value)
{
    m_prev_value = value;
    m_prev_time = (double)frc::Timer::GetFPGATimestamp();
}