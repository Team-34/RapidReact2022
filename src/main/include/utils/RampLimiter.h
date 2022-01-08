#pragma once

#include <frc/Timer.h>
#include <algorithm>


class RampLimiter
{
public:
    RampLimiter(double rate_limit = 1.0, double initial_value = 0.0);
    
    double Calculate(double input);
    
    void Reset(double value = 0.0);
    
private:
    double m_rate_limit;
    double m_prev_value;
    double m_prev_time;
};