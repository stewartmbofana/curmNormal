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

namespace univar
{
double DECLSPEC cumnorm(double x);
double DECLSPEC cumnorm6(double x);
double DECLSPEC NPrime(double x);
double DECLSPEC NPrimePrime(double x);
double DECLSPEC CumNormInverse(double y);
} // namespace trivar

#endif