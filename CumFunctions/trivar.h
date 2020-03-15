#ifndef GUARD_trivar_h
#define GUARD_trivar_h

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
#include "bivar.h"

namespace trivar
{
double DECLSPEC trivarcumnorm(double x, double y, double z, double correl12, double correl13, double correl23);
}

#endif;