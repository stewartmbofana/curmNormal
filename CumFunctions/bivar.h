#ifndef GUARD_bivar_h
#define GUARD_bivar_h

#if defined(_WIN32)
#if defined(EXPORTING_CUMNORM)
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif
#else // non windows
#define DECLSPEC
#endif

#include "univar.h"

namespace bivar
{
double DECLSPEC bivarcumnorm(double x, double y, double rho);
}

#endif;