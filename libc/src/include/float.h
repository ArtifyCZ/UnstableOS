#ifndef _FLOAT_H
#define _FLOAT_H

// because the x87 FPU works with 80 bit floats - long double
#define FLT_EVAL_METHOD 2
#define FLT_ROUNDS 1 // nearest, the fninit default rounding, TODO: change when fesetround()
#define FLT_RADIX 2

#define FLT_HAS_SUBNORM  1
#define DBL_HAS_SUBNORM  1
#define LDBL_HAS_SUBNORM 1

#define FLT_MIN_EXP  (-125)
#define DBL_MIN_EXP  (-1021)
#define LDBL_MIN_EXP (-16381)

#define FLT_MAX_EXP  (128)
#define DBL_MAX_EXP  (1024)
#define LDBL_MAX_EXP (16384)

#define FLT_MIN_10_EXP  (-37)
#define DBL_MIN_10_EXP  (-307)
#define LDBL_MIN_10_EXP (-4931)

#define FLT_MAX_10_EXP  (38)
#define DBL_MAX_10_EXP  (308)
#define LDBL_MAX_10_EXP (4932)

#define FLT_MANT_DIG 24
#define DBL_MANT_DIG 53
#define LDBL_MANT_DIG 64

#define FLT_DIG  6
#define DBL_DIG  15
#define LDBL_DIG 18
#define DECIMAL_DIG LDBL_DIG

// thank you trusty gnome calculator for having a binary float mode <3
#define FLT_EPSILON  (1.192092896e-07F)
#define DBL_EPSILON  (2.220446049e-16)
#define LDBL_EPSILON (1.084202172e-19L)

#define FLT_MIN  (1.175494351e-0038F)
#define DBL_MIN  (2.225073859e-0308)
#define LDBL_MIN (3.362103143e-4932L)

// the subnormal ones, that being exponent 0, mantissa nonzero
#define FLT_TRUE_MIN  (1.401298464e-0045F)
#define DBL_TRUE_MIN  (4.940656458e-0324)
#define LDBL_TRUE_MIN (3.645199532e-4951L)

#define FLT_MAX  (3.402823568e0038F)
#define DBL_MAX  (1.797693135e0308)
#define LDBL_MAX (1.189731495e4932L)
#endif