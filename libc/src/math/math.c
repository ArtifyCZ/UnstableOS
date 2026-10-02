#include <math.h>
// TODO: instead of these libgcc "stubs", implement the functions themselves to acquire the "coolness" factor
// a problem for future me <3

double acos(double x) {
    return __builtin_acos(x);
}
float acosf(float x) {
    return __builtin_acosf(x);
}
double acosh(double x) {
    return __builtin_acosh(x);
}
float acoshf(float x) {
    return __builtin_acoshf(x);
}
long double acoshl(long double x) {
    return __builtin_acoshl(x);
}
long double acosl(long double x) {
    return __builtin_acosl(x);
}

double asin(double x) {
    return __builtin_asin(x);
}
float asinf(float x) {
    return __builtin_asinf(x);
}
double asinh(double x) {
    return __builtin_asinh(x);
}
float asinhf(float x) {
    return __builtin_asinf(x);
}
long double asinhl(long double x) {
    return __builtin_asinhl(x);
}
long double asinl(long double x) {
    return __builtin_asinl(x);
}

double atan(double x) {
    return __builtin_atan(x);
}
double atan2(double x, double y) {
    return __builtin_atan2(x, y);
}
float atan2f(float x, float y) {
    return __builtin_atan2f(x, y);
}
long double atan2l(long double x, long double y) {
    return __builtin_atan2l(x, y);
}
float atanf(float x) {
    return __builtin_atanf(x);
}
double atanh(double x) {
    return __builtin_atanh(x);
}
float atanhf(float x) {
    return __builtin_atanhf(x);
}
long double atanhl(long double x) {
    return __builtin_atanhl(x);
}
long double atanl(long double x) {
    return __builtin_atanl(x);
}

double cbrt(double x) {
    return __builtin_cbrt(x);
}
float cbrtf(float x) {
    return __builtin_cbrtf(x);
}
long double cbrtl(long double x) {
    return __builtin_cbrtl(x);
}

double ceil(double x) {
    return __builtin_ceil(x);
}
float ceilf(float x) {
    return __builtin_ceilf(x);
}
long double ceill(long double x) {
    return __builtin_ceill(x);
}

double copysign(double x, double y) {
    return __builtin_copysign(x, y);
}
float copysignf(float x, float y) {
    return __builtin_copysignf(x, y);
}
long double copysignl(long double x, long double y) {
    return __builtin_copysignl(x, y);
}

double cos(double x) {
    return __builtin_cos(x);
}
float cosf(float x) {
    return __builtin_cosf(x);
}
double cosh(double x) {
    return __builtin_cosh(x);
}
float coshf(float x) {
    return __builtin_coshf(x);
}
long double coshl(long double x) {
    return __builtin_coshl(x);
}
long double cosl(long double x) {
    return __builtin_cosl(x);
}

double erf(double x) {
    return __builtin_erf(x);
}
double erfc(double x) {
    return __builtin_erfc(x);
}
float erfcf(float x) {
    return __builtin_erfcf(x);
}
long double erfcl(long double x) {
    return __builtin_erfcl(x);
}
float erff(float x) {
    return __builtin_erff(x);
}
long double erfl(long double x) {
    return __builtin_erfl(x);
}

double exp(double x) {
    return __builtin_exp(x);
}
double exp2(double x) {
    return __builtin_exp2(x);
}
float exp2f(float x) {
    return __builtin_exp2f(x);
}
long double exp2l(long double x) {
    return __builtin_exp2l(x);
}
float expf(float x) {
    return __builtin_expf(x);
}
long double expl(long double x) {
    return __builtin_expl(x);
}
double expm1(double x) {
    return __builtin_expm1(x);
}
float expm1f(float x) {
    return __builtin_expm1f(x);
}
long double expm1l(long double x) {
    return __builtin_expm1l(x);
}

double fabs(double x) {
    return __builtin_fabs(x);
}
float fabsf(float x) {
    return __builtin_fabsf(x);
}
long double fabsl(long double x) {
    return __builtin_fabsl(x);
}

double fdim(double x, double y) {
    return __builtin_fdim(x, y);
}
float fdimf(float x, float y) {
    return __builtin_fdimf(x, y);
}
long double fdiml(long double x, long double y) {
    return __builtin_fdiml(x, y);
}

double floor(double x) {
    return __builtin_floor(x);
}
float floorf(float x) {
    return __builtin_floorf(x);
}
long double floorl(long double x) {
    return __builtin_floorl(x);
}

double fma(double x, double y, double z) {
    return __builtin_fma(x, y, z);
}
float fmaf(float x, float y, float z) {
    return __builtin_fmaf(x, y, z);
}
long double fmal(long double x, long double y, long double z) {
    return __builtin_fmal(x, y, z);
}

double fmax(double x, double y) {
    return __builtin_fmax(x, y);
}
float fmaxf(float x, float y) {
    return __builtin_fmaxf(x, y);
}
long double fmaxl(long double x, long double y) {
    return __builtin_fmaxl(x, y);
}

double fmin(double x, double y) {
    return __builtin_fmin(x, y);
}
float fminf(float x, float y) {
    return __builtin_fminf(x, y);
}
long double fminl(long double x, long double y) {
    return __builtin_fminl(x, y);
}

double fmod(double x, double y) {
    return __builtin_fmod(x, y);
}
float fmodf(float x, float y) {
    return __builtin_fmodf(x, y);
}
long double fmodl(long double x, long double y) {
    return __builtin_fmodl(x, y);
}

double frexp(double num, int * exp) {
    return __builtin_frexp(num, exp);
}
float frexpf(float num, int * exp) {
    return __builtin_frexpf(num, exp);
}
long double frexpl(long double num, int * exp) {
    return __builtin_frexpl(num, exp);
}

double hypot(double x, double y) {
    return __builtin_hypot(x, y);
}
float hypotf(float x, float y) {
    return __builtin_hypotf(x, y);
}
long double hypotl(long double x, long double y) {
    return __builtin_hypotl(x, y);
}

int ilogb(double x) {
    return __builtin_ilogb(x);
}
int ilogbf(float x) {
    return __builtin_ilogbf(x);
}
int ilogbl(long double x) {
    return __builtin_ilogbl(x);
}

double j0(double x) {
    return __builtin_j0(x);
}
double j1(double x) {
    return __builtin_j1(x);
}
double jn(int n, double x) {
    return __builtin_jn(n, x);
}

double ldexp(double x, int exp) {
    return __builtin_ldexp(x, exp);
}
float ldexpf(float x, int exp) {
    return __builtin_ldexp(x, exp);
}
long double ldexpl(long double x, int exp) {
    return __builtin_ldexp(x, exp);
}

double lgamma(double x) {
    return __builtin_lgamma(x);
}
float lgammaf(float x) {
    return __builtin_lgammaf(x);
}
long double lgammal(long double x) {
    return __builtin_lgammal(x);
}

long long llrint(double x) {
    return __builtin_llrint(x);
}
long long llrintf(float x) {
    return __builtin_llrintf(x);
}
long long llrintl(long double x) {
    return __builtin_llrintl(x);
}

long long llround(double x) {
    return __builtin_llround(x);
}
long long llroundf(float x) {
    return __builtin_llroundf(x);
}
long long llroundl(long double x) {
    return __builtin_llroundl(x);
}

double log(double x) {
    return __builtin_log(x);
}
double log10(double x) {
    return __builtin_log10(x);
}
float log10f(float x) {
    return __builtin_log10f(x);
}
long double log10l(long double x) {
    return __builtin_log10l(x);
}
double log1p(double x) {
    return __builtin_log1p(x);
}
float log1pf(float x) {
    return __builtin_log1pf(x);
}
long double log1pl(long double x) {
    return __builtin_log1pl(x);
}
double log2(double x) {
    return __builtin_log2(x);
}
float log2f(float x) {
    return __builtin_log2f(x);
}
long double log2l(long double x) {
    return __builtin_log2l(x);
}
double logb(double x) {
    return __builtin_logb(x);
}
float logbf(float x) {
    return __builtin_logbf(x);
}
long double logbl(long double x) {
    return __builtin_logbl(x);
}
float logf(float x) {
    return __builtin_logf(x);
}
long double logl(long double x) {
    return __builtin_logl(x);
}

long lrint(double x) {
    return __builtin_lrint(x);
}
long lrintf(float x) {
    return __builtin_lrintf(x);
}
long lrintl(long double x) {
    return __builtin_lrintl(x);
}

long lround(double x) {
    return __builtin_lround(x);
}
long lroundf(float x) {
    return __builtin_lroundf(x);
}
long lroundl(long double x) {
    return __builtin_lroundl(x);
}

double modf(double x, double * iptr) {
    return __builtin_modf(x, iptr);
}
float modff(float value, float * iptr) {
    return __builtin_modff(value, iptr);
}
long double modfl(long double value, long double * iptr) {
    return __builtin_modfl(value, iptr);
}

double nan(const char * tagp) {
    return __builtin_nan(tagp);
}
float nanf(const char * tagp) {
    return __builtin_nanf(tagp);
}
long double nanl(const char * tagp) {
    return __builtin_nanl(tagp);
}

double nearbyint(double x) {
    return __builtin_nearbyint(x);
}
float nearbyintf(float x) {
    return __builtin_nearbyintf(x);
}
long double nearbyintl(long double x) {
    return __builtin_nearbyintl(x);
}

double nextafter(double x, double y) {
    return __builtin_nextafter(x, y);
}
float nextafterf(float x, float y) {
    return __builtin_nextafterf(x, y);
}
long double nextafterl(long double x, long double y) {
    return __builtin_nextafterl(x, y);
}

double nexttoward(double x, long double y) {
    return __builtin_nexttoward(x, y);
}
float nexttowardf(float x, long double y) {
    return __builtin_nexttowardf(x, y);
}
long double nexttowardl(long double x, long double y) {
    return __builtin_nexttowardl(x, y);
}

double pow(double x, double y) {
    return __builtin_pow(x, y);
}
float powf(float x, float y) {
    return __builtin_powf(x, y);
}
long double powl(long double x, long double y) {
    return __builtin_powl(x, y);
}

double remainder(double x, double y) {
    return __builtin_remainder(x, y);
}
float remainderf(float x, float y) {
    return __builtin_remainderf(x, y);
}
long double remainderl(long double x, long double y) {
    return __builtin_remainderl(x, y);
}

double remquo(double x, double y, int *quo) {
    return __builtin_remquo(x, y, quo);
}
float remquof(float x, float y, int *quo) {
    return __builtin_remquof(x, y, quo);
}
long double remquol(long double x, long double y, int *quo) {
    return __builtin_remquol(x, y, quo);
}

double rint(double x) {
    return __builtin_rint(x);
}
float rintf(float x) {
    return __builtin_rintf(x);
}
long double rintl(long double x) {
    return __builtin_rintl(x);
}

double round(double x) {
    return __builtin_round(x);
}
float roundf(float x) {
    return __builtin_round(x);
}
long double roundl(long double x) {
    return __builtin_round(x);
}

double scalbln(double x, long n) {
    return __builtin_scalbln(x, n);
}
float scalblnf(float x, long n) {
    return __builtin_scalblnf(x, n);
}
long double scalblnl(long double x, long n) {
    return __builtin_scalblnl(x, n);
}
double scalbn(double x, int n) {
    return __builtin_scalbn(x, n);
}
float scalbnf(float x, int n) {
    return __builtin_scalbnf(x, n);
}
long double scalbnl(long double x, int n) {
    return __builtin_scalbnl(x, n);
}

double sin(double x) {
    return __builtin_sin(x);
}
float sinf(float x) {
    return __builtin_sinf(x);
}
double sinh(double x) {
    return __builtin_sinh(x);
}
float sinhf(float x) {
    return __builtin_sinhf(x);
}
long double sinhl(long double x) {
    return __builtin_sinhl(x);
}
long double sinl(long double x) {
    return __builtin_sinl(x);
}

double sqrt(double x) {
    return __builtin_sqrt(x);
}
float sqrtf(float x) {
    return __builtin_sqrtf(x);
}
long double sqrtl(long double x) {
    return __builtin_sqrtl(x);
}

double tan(double x) {
    return __builtin_tan(x);
}
float tanf(float x) {
    return __builtin_tanf(x);
}
double tanh(double x) {
    return __builtin_tanh(x);
}
float tanhf(float x) {
    return __builtin_tanhf(x);
}
long double tanhl(long double x) {
    return __builtin_tanhl(x);
}
long double tanl(long double x) {
    return __builtin_tanl(x);
}

double tgamma(double x) {
    return __builtin_tgamma(x);
}
float tgammaf(float x) {
    return __builtin_tgammaf(x);
}
long double tgammal(long double x) {
    return __builtin_tgammal(x);
}

double trunc(double x) {
    return __builtin_trunc(x);
}
float truncf(float x) {
    return __builtin_truncf(x);
}
long double truncl(long double x) {
    return __builtin_truncl(x);
}

double y0(double x) {
    return __builtin_y0(x);
}
double y1(double x) {
    return __builtin_y1(x);
}
double yn(int n, double x) {
    return __builtin_yn(n, x);
}