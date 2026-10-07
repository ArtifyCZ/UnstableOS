#include <math.h>
#include <float.h>
#include <stdint.h>

#define DBL_EXP_MASK 0x7FF
#define LDBL_EXP_MASK 0x7FFF
#define DBL_EXP_DELTA 0x3FF
#define LDBL_EXP_DELTA 0x3FFF

double modf(double x, double * iptr) {
    if (fpclassify(x) == FP_NAN) {
        *iptr = x;
        return x;
    }

    union {double f; uint64_t i;} u = {.f = x};
    int exp = (int)(u.i >> (DBL_MANT_DIG - 1) & DBL_EXP_MASK);
    exp -= DBL_EXP_DELTA;

    // the mantissa has no bits representing a whole number
    if (exp < 0) {
        // save the sign
        u.i &= 0x8000000000000000ULL;
        *iptr = u.f;
        return x;
    }

    // the mantissa has no bits representing a fraction
    if (exp >= DBL_MANT_DIG - 1) {
        nofrac:
        *iptr = x;
        // save the sign
        u.i &= 0x8000000000000000ULL;
        return u.f;
    }

    // parts to the left correspond to whole numbers
    uint64_t frac_part = (1ULL << (DBL_MANT_DIG - exp)) - 1;
    if ((u.i & frac_part) == 0)
        goto nofrac;

    u.i &= ~frac_part;
    *iptr = u.f;
    return x - u.f;
}

long double modfl(long double x, long double * iptr) {
    if (fpclassify(x) == FP_NAN) {
        *iptr = x;
        return x;
    }

    union {long double f; struct {uint64_t m; uint16_t e;};} u = {.f = x};
    int exp = u.e & LDBL_EXP_MASK;
    exp -= LDBL_EXP_DELTA;

    // the mantissa has no bits representing a whole number
    if (exp < 0) {
        // save the sign
        u.e &= 0x8000;
        *iptr = u.f;
        return x;
    }

    // the mantissa has no bits representing a fraction
    if (exp >= LDBL_MANT_DIG - 1) {
        nofrac:
        *iptr = x;
        // save the sign
        u.e &= 0x8000;
        return u.f;
    }

    // parts to the left correspond to whole numbers
    // -1 because of the integer bit present on x87
    uint64_t frac_part = (1ULL << (LDBL_MANT_DIG - exp - 1)) - 1;
    if ((u.m & frac_part) == 0)
        goto nofrac;

    u.m &= ~frac_part;
    *iptr = u.f;
    return x - u.f;
}

float modff(float value, float * iptr) {
    double i;
    double ret = modf(value, &i);
    *iptr = (float)i;
    return ret;
}