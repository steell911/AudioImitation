/**************************************************************************
** Qt Creator license header template
**   Special keywords:  25.01.2018 2018
**   Environment variables:
**   To protect a percent sign, use '%'.
**************************************************************************/
//	date: 25.01.2018
//	file: converter.h

#ifndef CONVERTER_H
#define CONVERTER_H

namespace converter {

template <typename T>
void polarToRectangular(T radius,
                         T zenith,
                         T azimuth,
                         T* rectangular);

extern template void polarToRectangular(float, float, float, float*);
extern template void polarToRectangular(double, double, double, double*);
extern template void polarToRectangular(long double, long double, long double, long double*);

}

#endif // CONVERTER_H
