/**************************************************************************
** Qt Creator license header template
**   Special keywords:  25.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 25.01.2018
//	file: converter.cpp

#include "converter.h"
#include <cmath>

namespace converter {

template <typename T>
    void polarToRectangular(T radius,
                             T zenith,
                             T azimuth,
                             T* rectangular)
    {
        rectangular[0] = radius*sin(zenith)*cos(azimuth);
        rectangular[1] = radius*sin(zenith)*sin(azimuth);
        rectangular[2] = radius*cos(zenith);
    }

    template void polarToRectangular(float, float, float, float*);
    template void polarToRectangular(double, double, double, double*);
    template void polarToRectangular(long double, long double, long double, long double*);


}
