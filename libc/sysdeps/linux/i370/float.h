/* float.h for IBM i370 target, which uses HFP "Hex Floating Point".
   This is NOT IEEE float, aka BFP "Binary Floating Point".

   See Enterprise Systems Architecture/390
   Principles of Operation Ninth Edition (June, 2003) SA22-7201-08
   See chapters 9 and 18.

   Floats are 32-bit, doubles are 64-bit long doubles are 128-bit.
   All have a 7-bit "characteristic" equal to exponent plus 64.

   Hex means the radix is 16 (and not 2) and thus min and max
   representable numbers are 16**-64 and 16**63 (plus, minus one in
   the last place.) All have the same range and differ only in
   precision.
 */
#ifndef _FLOAT_H_
#define _FLOAT_H_

   /* Radix of exponent representation */
#undef FLT_RADIX
#define FLT_RADIX 16

   /* Number of base-FLT_RADIX digits in the significand of a float */
   /* 3 bytes, 6 nibbles in the mantissa. */
#undef FLT_MANT_DIG
#define FLT_MANT_DIG 6
   /* Number of decimal digits of precision in a float */
   /* 2^23 is 8M so about 7 digits decimal. */
#undef FLT_DIG
#define FLT_DIG 7
   /* Addition rounds to 0: zero, 1: nearest, 2: +inf, 3: -inf, -1: unknown */
#undef FLT_ROUNDS
#define FLT_ROUNDS 1
   /* Difference between 1.0 and the minimum float greater than 1.0 */
   /* Equals 1.0/(1<<23) */
#undef FLT_EPSILON
#define FLT_EPSILON 1.19209290e-07F
   /* Minimum int x such that FLT_RADIX**(x-1) is a normalised float */
   /* Radix is 16, so 16**(-65) is smallest normalized float. */
#undef FLT_MIN_EXP
#define FLT_MIN_EXP (-64)
   /* Minimum normalised float. Equal to 16**(-65) */
#undef FLT_MIN
#define FLT_MIN 5.3976053e-79F
   /* Minimum int x such that 10**x is a normalised float */
#undef FLT_MIN_10_EXP
#define FLT_MIN_10_EXP (-78)
   /* Maximum int x such that FLT_RADIX**(x-1) is a representable float */
#undef FLT_MAX_EXP
#define FLT_MAX_EXP 64
   /* Maximum float. Equal to 16**63 */
#undef FLT_MAX
#define FLT_MAX 7.2370056e+75F
   /* Maximum int x such that 10**x is a representable float */
#undef FLT_MAX_10_EXP
#define FLT_MAX_10_EXP 75

   /* Number of base-FLT_RADIX digits in the significand of a double */
   /* 7 bytes, 14 nibbles. */
#undef DBL_MANT_DIG
#define DBL_MANT_DIG 14
   /* Number of decimal digits of precision in a double */
#undef DBL_DIG
#define DBL_DIG 16
   /* Difference between 1.0 and the minimum double greater than 1.0 */
   /* Equal to 1 / (2<<55) */
#undef DBL_EPSILON
#define DBL_EPSILON 2.7755575615628914e-17
   /* Minimum int x such that FLT_RADIX**(x-1) is a normalised double */
   /* Same as for floats. */
#undef DBL_MIN_EXP
#define DBL_MIN_EXP FLT_MIN_EXP
   /* Minimum normalised double */
   /* Same as for floats */
#undef DBL_MIN
#define DBL_MIN 5.397605346934028e-79
   /* Minimum int x such that 10**x is a normalised double */
   /* Same as for floats */
#undef DBL_MIN_10_EXP
#define DBL_MIN_10_EXP FLT_MIN_10_EXP
   /* Maximum int x such that FLT_RADIX**(x-1) is a representable double */
   /* Same as for floats */
#undef DBL_MAX_EXP
#define DBL_MAX_EXP FLT_MAX_EXP
   /* Maximum double */
   /* Same as for floats */
#undef DBL_MAX
#define DBL_MAX 7.237005577332262e+75
   /* Maximum int x such that 10**x is a representable double */
   /* Same as for floats */
#undef DBL_MAX_10_EXP
#define DBL_MAX_10_EXP FLT_MAX_10_EXP

   /* Number of base-FLT_RADIX digits in the significand of a long double */
#undef LDBL_MANT_DIG
#define LDBL_MANT_DIG 28
   /* Number of decimal digits of precision in a long double */
   /* Obtained from 16**28 */
#undef LDBL_DIG
#define LDBL_DIG 33
   /* Difference between 1.0 and the minimum long double greater than 1.0 */
   /* Should be 1 / (1<<111) */
#undef LDBL_EPSILON
#define LDBL_EPSILON 3.851859888774472e-34L
   /* Minimum int x such that FLT_RADIX**(x-1) is a normalised long double */
   /* Same as float */
#undef LDBL_MIN_EXP
#define LDBL_MIN_EXP FLT_MIN_EXP
   /* Minimum normalised long double */
   /* Same as float */
#undef LDBL_MIN
#define LDBL_MIN 5.397605346934028e-79L
   /* Minimum int x such that 10**x is a normalised long double */
   /* Same as float */
#undef LDBL_MIN_10_EXP
#define LDBL_MIN_10_EXP FLT_MIN_EXP
   /* Maximum int x such that FLT_RADIX**(x-1) is a representable long double */
   /* Same as float */
#undef LDBL_MAX_EXP
#define LDBL_MAX_EXP FLT_MAX_EXP
   /* Maximum long double */
   /* Same as float */
#undef LDBL_MAX
#define LDBL_MAX 7.237005577332262e+75L
   /* Maximum int x such that 10**x is a representable long double */
   /* Same as float */
#undef LDBL_MAX_10_EXP
#define LDBL_MAX_10_EXP FLT_MAX_10_EXP

#endif /*  _FLOAT_H_ */
