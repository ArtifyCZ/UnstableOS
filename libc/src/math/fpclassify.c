#include <math.h>
#include <float.h>
#include <stdint.h>
#define FLT_EXP_MASK 0xFF
#define DBL_EXP_MASK 0x7FF
#define LDBL_EXP_MASK 0x7FFF

int __fpclassify_f(float f) {
    union {float f; uint32_t i;} u = {.f = f};
    unsigned int exp = u.i >> (FLT_MANT_DIG - 1) & FLT_EXP_MASK;
    unsigned int sig = u.i & ((1 << (FLT_MANT_DIG - 1)) - 1);
    if (exp == 0)            return sig ? FP_SUBNORMAL : FP_ZERO;
    if (exp == FLT_EXP_MASK) return sig ? FP_NAN : FP_INFINITE;
    return FP_NORMAL;
}

int __fpclassify_d(double f) {
    union {double f; uint64_t i;} u = {.f = f};
    uint64_t exp = u.i >> (DBL_MANT_DIG - 1) & DBL_EXP_MASK;
    uint64_t sig = u.i & (((uint64_t)1 << (DBL_MANT_DIG - 1)) - 1);
    if (exp == 0)            return sig ? FP_SUBNORMAL : FP_ZERO;
    if (exp == DBL_EXP_MASK) return sig ? FP_NAN : FP_INFINITE;
    return FP_NORMAL;
}

int __fpclassify_ld(long double f) {
    // sometimes I think Intel is ragebaiting...
    // Intel SDM 4-5 Numeric Data Types, saying what is what
    // Intel SDM 8-13 Double Extended Precision Floating-Point, saying what is unsupported
    // and from those the integer invalid encoding edge case
    // Integer bit at mantissa msb
    union {long double f; struct {uint64_t m; uint16_t e;};} u = {.f = f};
    u.e &= 0x7FFF; // strip the sign bit
    unsigned char msb = u.m >> 63;
    u.m = (u.m << 1) >> 1;

    if (u.e == 0 && !msb)    return u.m ? FP_SUBNORMAL : FP_ZERO;
    if (!msb)                return FP_NAN; // invalid encoding
    if (u.e == LDBL_EXP_MASK)return u.m ? FP_NAN : FP_INFINITE;
    return FP_NORMAL;
}