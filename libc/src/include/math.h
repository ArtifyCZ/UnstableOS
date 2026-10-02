#ifndef _MATH_H
#define _MATH_H

// refer to float.h FLT_EVAL_METHOD
typedef long double float_t;
typedef long double double_t;

#define NAN (0.0F/0.0F)
#define INFINITY (1e6000F) // long double max (with the x87) is 1e4932
#define HUGE_VALF (INFINITY)
#define HUGE_VAL  ((double)INFINITY)
#define HUGE_VALL ((long double)INFINITY)

#define M_E        2.71828182845904523536
#define M_EGAMMA   0.57721566490153286060
#define M_LOG2E    1.44269504088896340735
#define M_LOG10E   4.34294481903251827651e-1
#define M_LN2      6.93147180559945309417e-1
#define M_LN10     2.30258509299404568402
#define M_PHI      1.61803398874989484820
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     7.85398163397448309616e-1
#define M_1_PI     3.18309886183790671538e-1
#define M_1_SQRTPI 5.64189583547756286948e-1
#define M_2_PI     6.36619772367581343076e-1
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT3    1.73205080756887729353
#define M_SQRT1_2  7.07106781186547524401e-1
#define M_SQRT1_3  5.77350269189625764509e-1

#define M_El        2.71828182845904523536L
#define M_EGAMMAl   0.57721566490153286060L
#define M_LOG2El    1.44269504088896340735L
#define M_LOG10El   4.34294481903251827651e-1L
#define M_LN2l      6.93147180559945309417e-1L
#define M_LN10l     2.30258509299404568402L
#define M_PHIl      1.61803398874989484820L
#define M_PIl       3.14159265358979323846L
#define M_PI_2l     1.57079632679489661923L
#define M_PI_4l     7.85398163397448309616e-1L
#define M_1_PIl     3.18309886183790671538e-1L
#define M_1_SQRTPIl 5.64189583547756286948e-1L
#define M_2_PIl     6.36619772367581343076e-1L
#define M_2_SQRTPIl 1.12837916709551257390L
#define M_SQRT2l    1.41421356237309504880L
#define M_SQRT3l    1.73205080756887729353L
#define M_SQRT1_2l  7.07106781186547524401e-1L
#define M_SQRT1_3l  5.77350269189625764509e-1L

#define FP_ZERO      0
#define FP_NORMAL    1
#define FP_SUBNORMAL 2
#define FP_INFINITE  3
#define FP_NAN       4

int __fpclassify_f(float f);
int __fpclassify_d(double f);
int __fpclassify_ld(long double f);

#define fpclassify(x) (                 \
    sizeof(x) == sizeof(float) ?        \
        __fpclassify_f(x) :             \
        sizeof(x) == sizeof(double) ?   \
            __fpclassify_d(x) :         \
            __fpclassify_ld(x)          \
)
// these could possibly be done with some bit magic, but ehh
#define isnormal(x) (fpclassify(x) == FP_NORMAL)
#define isinf(x)    (fpclassify(x) == FP_INFINITE)
#define isnan(x)    (fpclassify(x) == FP_NAN)
#define isfinite(x) (fpclassify(x) < FP_INFINITE)

static __inline int __signbit_f(float f) {
    union {float f; unsigned long i;} u = {.f = f};
    return u.i >> 31;
}
static __inline int __signbit_d(double f) {
    union {double f; unsigned long long i;} u = {.f = f};
    return u.i >> 63;
}
static __inline int __signbit_ld(long double f) {
    union {long double f; struct {unsigned long long m; unsigned short e;};} u = {.f = f};
    return u.e >> 15;
}

#define signbit(x) (                   \
    sizeof(x) == sizeof(float) ?       \
        __signbit_f(x) :               \
        sizeof(x) == sizeof(double) ?  \
            __signbit_d(x) :           \
            __signbit_ld(x)            \
)

#define isunordered(x, y) (isnan(x) || isnan(y))

#define __op_macro(x, y, op) (!isunordered(x, y) && (x) op (y))
#define isless(x, y)         __op_macro(x, y, <)
#define islessequal(x, y)    __op_macro(x, y, <=)
#define islessgreater(x, y)  __op_macro(x, y, !=)
#define isgreater(x, y)      __op_macro(x, y, >)
#define isgreaterequal(x, y) __op_macro(x, y, >=)

double      acos(double x);
float       acosf(float x);
double      acosh(double x);
float       acoshf(float x);
long double acoshl(long double x);
long double acosl(long double x);

double      asin(double x);
float       asinf(float x);
double      asinh(double x);
float       asinhf(float x);
long double asinhl(long double x);
long double asinl(long double x);

double      atan(double x);
double      atan2(double x, double y);
float       atan2f(float x, float y);
long double atan2l(long double x, long double y);
float       atanf(float x);
double      atanh(double x);
float       atanhf(float x);
long double atanhl(long double x);
long double atanl(long double x);

double      cbrt(double x);
float       cbrtf(float x);
long double cbrtl(long double x);

double      ceil(double x);
float       ceilf(float x);
long double ceill(long double x);

double      copysign(double x, double y);
float       copysignf(float x, float y);
long double copysignl(long double x, long double y);

double      cos(double x);
float       cosf(float x);
double      cosh(double x);
float       coshf(float x);
long double coshl(long double x);
long double cosl(long double x);

double      erf(double x);
double      erfc(double x);
float       erfcf(float x);
long double erfcl(long double x);
float       erff(float x);
long double erfl(long double x);

double      exp(double x);
double      exp2(double x);
float       exp2f(float x);
long double exp2l(long double x);
float       expf(float x);
long double expl(long double x);
double      expm1(double x);
float       expm1f(float x);
long double expm1l(long double x);

double      fabs(double x);
float       fabsf(float x);
long double fabsl(long double x);

double      fdim(double x, double y);
float       fdimf(float x, float y);
long double fdiml(long double x, long double y);

double      floor(double x);
float       floorf(float x);
long double floorl(long double x);

double      fma(double x, double y, double z);
float       fmaf(float x, float y, float z);
long double fmal(long double x, long double y, long double z);

double      fmax(double x, double y);
float       fmaxf(float x, float y);
long double fmaxl(long double x, long double y);

double      fmin(double x, double y);
float       fminf(float x, float y);
long double fminl(long double x, long double y);

double      fmod(double x, double y);
float       fmodf(float x, float y);
long double fmodl(long double x, long double y);

double      frexp(double num, int * exp);
float       frexpf(float num, int * exp);
long double frexpl(long double num, int * exp);

double      hypot(double x, double y);
float       hypotf(float x, float y);
long double hypotl(long double x, long double y);

int         ilogb(double x);
int         ilogbf(float x);
int         ilogbl(long double x);

double      j0(double x);
double      j1(double x);
double      jn(int n, double x);

double      ldexp(double x, int exp);
float       ldexpf(float x, int exp);
long double ldexpl(long double x, int exp);

double      lgamma(double x);
float       lgammaf(float x);
long double lgammal(long double x);

long long   llrint(double x);
long long   llrintf(float x);
long long   llrintl(long double x);

long long   llround(double x);
long long   llroundf(float x);
long long   llroundl(long double x);

double      log(double x);
double      log10(double x);
float       log10f(float x);
long double log10l(long double x);
double      log1p(double x);
float       log1pf(float x);
long double log1pl(long double x);
double      log2(double x);
float       log2f(float x);
long double log2l(long double x);
double      logb(double x);
float       logbf(float x);
long double logbl(long double x);
float       logf(float x);
long double logl(long double x);

long        lrint(double x);
long        lrintf(float x);
long        lrintl(long double x);

long        lround(double x);
long        lroundf(float x);
long        lroundl(long double x);

// mr posix why are these arguments called different :c
double      modf(double x, double * iptr);
float       modff(float value, float * iptr);
long double modfl(long double value, long double * iptr);

double      nan(const char * tagp);
float       nanf(const char * tagp);
long double nanl(const char * tagp);

double      nearbyint(double x);
float       nearbyintf(float x);
long double nearbyintl(long double x);

double      nextafter(double x, double y);
float       nextafterf(float x, float y);
long double nextafterl(long double x, long double y);

double      nexttoward(double x, long double y);
float       nexttowardf(float x, long double y);
long double nexttowardl(long double x, long double y);

double      pow(double x, double y);
float       powf(float x, float y);
long double powl(long double x, long double y);

double      remainder(double x, double y);
float       remainderf(float x, float y);
long double remainderl(long double x, long double y);

double      remquo(double x, double y, int *quo);
float       remquof(float x, float y, int *quo);
long double remquol(long double x, long double y, int *quo);

double      rint(double x);
float       rintf(float x);
long double rintl(long double x);

double      round(double x);
float       roundf(float x);
long double roundl(long double x);

double      scalbln(double x, long n);
float       scalblnf(float x, long n);
long double scalblnl(long double x, long n);
double      scalbn(double x, int n);
float       scalbnf(float x, int n);
long double scalbnl(long double x, int n);

double      sin(double x);
float       sinf(float x);
double      sinh(double x);
float       sinhf(float x);
long double sinhl(long double x);
long double sinl(long double x);

double      sqrt(double x);
float       sqrtf(float x);
long double sqrtl(long double x);

double      tan(double x);
float       tanf(float x);
double      tanh(double x);
float       tanhf(float x);
long double tanhl(long double x);
long double tanl(long double x);

double      tgamma(double x);
float       tgammaf(float x);
long double tgammal(long double x);

double      trunc(double x);
float       truncf(float x);
long double truncl(long double x);

double      y0(double x);
double      y1(double x);
double      yn(int n, double x);
#endif