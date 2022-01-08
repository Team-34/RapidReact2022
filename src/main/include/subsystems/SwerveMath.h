#pragma once

#include <cmath>

constexpr double PI{ 3.1415926535897932384626433832 };

constexpr double _180_DIV_PI(){ return 180.0 / PI; }

constexpr double _PI_DIV_180(){ return PI / 180.0; }

constexpr double FULL_UNITS{ 36864.0 };

constexpr double FRAME_LENGTH{ 29.0 };
constexpr double FRAME_WIDTH{ 29.0 };

constexpr double _45_DEG( 4608.0);
constexpr double _135_DEG( 3 * 4608.0); 
constexpr double _225_DEG( 5 * 4608.0);
constexpr double _315_DEG( 7 * 4608.0);

constexpr double RATIO() { 
            return sqrt(
                (FRAME_LENGTH * FRAME_LENGTH) + 
                (FRAME_WIDTH * FRAME_WIDTH)); 
        }
        
constexpr double FRAME_LENGTH_DIV_RATIO() { 
            return FRAME_LENGTH / RATIO(); 
        }
        
constexpr double FRAME_WIDTH_DIV_RATIO() { 
            return FRAME_WIDTH / RATIO(); 
        }

inline double sqr(double d) { return d * d; }
inline double deg_to_rad(double deg) { return deg * _PI_DIV_180(); }
inline double rad_to_deg(double rad) { return rad * _180_DIV_PI(); }