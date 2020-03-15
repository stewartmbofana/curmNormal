#ifndef GUARD_univar_h
#define GUARD_univar_h

#if defined(_WIN32)
#if defined(EXPORTING_CUMNORM)
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif
#else // non windows
#define DECLSPEC
#endif

namespace trivar
{
double cumnorm(double x);
double cumnorm6(double x);
double NPrime(double x);
double NPrimePrime(double x);
double CumNormInverse(double y);
} // namespace trivar

#endif