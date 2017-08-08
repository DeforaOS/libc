/* $Id$ */
/* Copyright (c) 2008-2017 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
/* XXX from dietlibc */



#include "sys/types.h"
#include "math.h"
#include "arch.h"


/* constants */
#define B0      +            1.0l/   6/ 1/ 2
#define B1      -            1.0l/  30/ 3/ 4
#define B2      +            1.0l/  42/ 5/ 6
#define B3      -            1.0l/  30/ 7/ 8
#define B4      +            5.0l/  66/ 9/10
#define B5      -          691.0l/2730/11/12
#define B6      +            7.0l/   6/13/14
#define B7      -         3617.0l/ 510/15/16
#define B8      +        43867.0l/ 798/17/18
#define B9      -       174611.0l/ 330/19/20
#define B10     +       854513.0l/ 138/21/22
#define B11     -    236364091.0l/2730/23/24
#define B12     +      8553103.0l/   6/25/26

#define M_C		0.5772156649015328


/* variables */
static const double _coeff[] = { B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10 };
static int _signgam;


/* macros */
#define EXPL(x)   ((((short *)(void *)&x)[4] & 0x7FFF) >> 0)
#define EXPD(x)   ((((short *)(void *)&x)[3] & 0x7FF0) >> 4)
#define EXPF(x)   ((((short *)(void *)&x)[1] & 0x7F80) >> 7)

#define SQUARE(x) (long) (My - (x) * (x) )


/* prototypes */
/* private */
static double _logfact(long double x);
static double _poly(double x, size_t n, const double * c);

static long double _P(int My, double * x);
static long double _Q(int My, double * x);
static long double _jn(int n, double * x);
static long double _yn(int n, double * x);


/* functions */
/* private */
static double _logfact(long double x)
{
	static unsigned char list [] = { 6, 4, 3, 3, 2, 2 };
	long double   z = 2. * M_PI * x;
	register int  e = EXPL (x);

	return (log(x) - 1) * x + 0.5 * log(z) + _poly(1. / (x * x),
			e < 0x4003 ? 10 : (e > 0x4008 ? 1 : list[e - 0x4003]),
			_coeff) / x;
}


static double _poly(double x, size_t n, const double * c)
{
	long double ret;
	size_t i;

	i = n;
	c += n;
	ret = 0;
	do
		ret = ret * x + *c--;
	while(i--);
	return ret;
}


static long double _P(int My, double * x)
{
    long double Sum  = 0.;
    long double Fact = 1.;
    long double z182 = -0.015625 / (x[0] * x[0]);
    register int i;

    for ( i = 1; ; i += 2 ) {
        Fact *= SQUARE(i+i-1) * SQUARE(i+i+1) * z182 / (i*(i+1));
        if ( EXPL (Fact) < 0x3FFF-53 )
            break;
        Sum  += Fact;
    }
    return 1. + Sum;
}


static long double _Q(int My, double * x)
{
    long double Fact = (My-1) / x[0] * 0.125;
    long double Sum  = Fact;
    long double z182 = -0.015625 / (x[0]*x[0]);
    register int i;

    for ( i = 2; ; i += 2 ) {
        Fact *= SQUARE(i+i-1) * SQUARE(i+i+1) * z182 / (i*(i+1));
        if ( EXPL (Fact) < 0x3FFF-53 )
            break;
        Sum  += Fact;
    }
    return Sum;
}


static long double _jn(int n, double * x)
{
    long double   Sum;
    long double   Fact;
    long double   y;
    register int  i;
    double        xx;
    long double   Xi;
    int           My;

    if ( n < 0 )
        return n & 1 ? _jn(-n, x) : -_jn(-n, x);

    if ((x[0] >= 17.7+0.0144*(n*n))) {
        Xi = x[0] - M_PI * (n*0.5 + 0.25);
        My = n*n << 2;

        return sqrt(M_2_PI / x[0]) * (_P(My, x) * cos(Xi) - _Q(My,x) * sin(Xi));
    }
    xx   = x[0] * 0.5;
    Sum  = 0.;
    Fact = 1.;
    y    = -xx * xx;

    for ( i = 1; i <= n; i++ )
        Fact *= xx/i;
    for ( i = 1; ; i++ ) {
        Sum  += Fact;
        Fact *= y / (i*(n+i));
        if ( EXPL (Sum) - EXPL(Fact) > 53 || !EXPL(Fact) )
            break;
    }
    return Sum;
}


static long double  _yn ( int n, double* x )
{
    long double   Sum1;
    long double   Sum2;
    long double   Fact1;
    long double   Fact2;
    long double   F1;
    long double   F2;
    long double   y;
    register int  i;
    double        xx;
    long double   Xi;
    unsigned int  My;

    if ( EXPD (x[0]) == 0 )
        return -1./0.;	/* ignore the gcc warning, this is intentional */

    if ( (x[0] >= (n>=32 ? 25.8 : (n<8 ? 17.4+0.1*n : 16.2+0.3*n))) ) {
        Xi = x[0] - M_PI * (n*0.5+0.25);
        My = n*n << 2;

        return sqrt(M_2_PI / x[0]) * (_P(My,x) * sin(Xi) + _Q(My,x) * cos(Xi));
    }

    Sum1  = Sum2 = F1 = F2 = 0;
    Fact1 = 1. / (xx = x[0] * 0.5 );
    Fact2 = 1.;
    y     = xx*xx;

    for ( i = 1; i < n; i++ )
        Fact1 *= (n-i) / xx;

    for ( i = 1; i <= n; i++ ) {
        Sum1  += Fact1;
        if ( i == n )
            break;
        Fact1 *= y/(i*(n-i));
    }

    for (i=1; i<=n; i++) {
        Fact2 *= xx / i;
        F1    += 1. / i;
    }

    for ( i = 1; ; i++ ) {
        Sum2  += Fact2 * (F1+F2);
        Fact2 *= -y / (i*(n+i));
        if ( EXPL (Sum2) - EXPL (Fact2) > 53 || !EXPL (Fact2) )
            break;
        F1 += 1. / (n+i);
        F2 += 1. / i;
    }

    return M_1_PI * (2. * (M_C + log(xx)) * _jn (n, x) - Sum1 - Sum2);
}


/* public */
#if 0
double acos(double);
float acosf(float);
double acosh(double);
float acoshf(float);
long double acoshl(long double);
long double acosl(long double);
double asin(double);
float asinf(float);
double asinh(double);
float asinhf(float);
long double asinhl(long double);
long double asinl(long double);
#endif


/* atan */
#ifndef ARCH_atan
double atan(double x)
{
	return atanl(x);
}
#endif


/* atan2 */
#ifndef ARCH_atan2
double atan2(double x, double y)
{
	return atan2l(x, y);
}
#endif


/* atan2f */
#ifndef ARCH_atan2f
float atan2f(float x, float y)
{
	return atan2(x, y);
}
#endif


/* atan2l */
#ifndef ARCH_atan2l
long double atan2l(long double x, long double y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* atanf */
#ifndef ARCH_atanf
float atanf(float x)
{
	return atan(x);
}
#endif


/* atanh */
#ifndef ARCH_atanh
double atanh(double x)
{
	return atanhl(x);
}
#endif


/* atanhf */
#ifndef ARCH_atanhf
float atanhf(float x)
{
	return atanh(x);
}
#endif


/* atanhl */
#ifndef ARCH_atanhl
# warning Unsupported platform: atanhl() is not implemented
long double atanhl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* atanl */
#ifndef ARCH_atanl
# warning Unsupported platform: atanl() is not implemented
long double atanl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
double cbrt(double);
float cbrtf(float);
long double cbrtl(long double);
#endif


/* ceil */
#ifndef ARCH_ceil
double ceil(double x)
{
	return ceill(x);
}
#endif


/* ceilf */
#ifndef ARCH_ceilf
float ceilf(float x)
{
	return ceil(x);
}
#endif


/* ceill */
#ifndef ARCH_ceill
long double ceill(long double x)
{
	long double y;

	y = round(x);
	return (y >= x) ? y : y + 1.0;
}
#endif


#if 0
double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);
#endif


/* cos */
#ifndef ARCH_cos
double cos(double x)
{
	return cosl(x);
}
#endif


/* cosf */
float cosf(float x)
{
	return cos(x);
}


#if 0
double cosh(double);
float coshf(float);
long double coshl(long double);
#endif


/* cosl */
#ifndef ARCH_cosl
# warning Unsupported platform: cosl() is not implemented
long double cosl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
double erf(double);
double erfc(double);
float erfcf(float);
long double erfcl(long double);
float erff(float);
long double erfl(long double);
#endif


/* exp */
#ifndef ARCH_exp
double exp(double x)
{
	return expl(x);
}
#endif


#if 0
double exp2(double);
float exp2f(float);
long double exp2l(long double);
#endif


/* expf */
#ifndef ARCH_expf
float expf(float x)
{
	return exp(x);
}
#endif


/* expl */
#ifndef ARCH_expl
# warning Unsupported platform: expl() is not implemented
long double expl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
double expm1(double);
float expm1f(float);
long double expm1l(long double);
#endif


/* fabs */
#ifndef ARCH_fabs
double fabs(double x)
{
	return (x >= 0.0) ? x : -x;
}
#endif


/* fabsf */
#ifndef ARCH_fabsf
float fabsf(float x)
{
	return (x >= 0.0) ? x : -x;
}
#endif


/* fabsl */
#ifndef ARCH_fabsl
long double fabsl(long double x)
{
	return (x >= 0.0) ? x : -x;
}
#endif


#if 0
double fdim(double, double);
float fdimf(float, float);
long double fdiml(long double, long double);
#endif


/* floor */
#ifndef ARCH_floor
double floor(double x)
{
	return floorl(x);
}
#endif


/* floorf */
#ifndef ARCH_floorf
float floorf(float x)
{
	return floor(x);
}
#endif


#ifndef ARCH_floorl
long double floorl(long double x)
{
	long double y;

	y = round(x);
	return (y <= x) ? y : y - 1.0;
}
#endif


#if 0
double fma(double, double, double);
float fmaf(float, float, float);
long double fmal(long double, long double, long double);
double fmax(double, double);
float fmaxf(float, float);
long double fmaxl(long double, long double);
double fmin(double, double);
float fminf(float, float);
long double fminl(long double, long double);
#endif


/* fmod */
#ifndef ARCH_fmod
double fmod(double x, double y)
{
	return fmodl(x, y);
}
#endif


/* fmod */
#ifndef ARCH_fmodf
float fmodf(float x, float y)
{
	return fmod(x, y);
}
#endif


#ifndef ARCH_fmodl
long double fmodl(long double x, long double y)
{
	long double z;

	z = floor(x / y);
	return x - (y * z);
}
#endif


/* frexp */
#ifndef ARCH_frexp
# warning Unsupported platform: frexp() is not implemented
double frexp(double x, int * y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* frexpf */
#ifndef ARCH_frexpf
# warning Unsupported platform: frexpf() is not implemented
float frexpf(float value, int * y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
long double frexpl(long double value, int *);
#endif


/* hypot */
#ifndef ARCH_hypot
double hypot(double x, double y)
{
	return hypotl(x, y);
}
#endif


/* hypotf */
#ifndef ARCH_hypotf
float hypotf(float x, float y)
{
	return hypot(x, y);
}
#endif


/* hypotl */
#ifndef ARCH_hypotl
long double hypotl(long double x, long double y)
{
	/* XXX may overflow */
	return sqrt((x * x) + (y * y));
}
#endif


#if 0
int ilogb(double);
int ilogbf(float);
int ilogbl(long double);
int isinf(float x);
#endif
/* isnan */
int isnan(float x)
{
	/* FIXME implement */
	return 1;
}


/* j0 */
double j0(double x)
{
	return _jn(0, &x);
}


/* j1 */
double j1(double x)
{
	return _jn(1, &x);
}


/* jn */
double jn(int n, double x)
{
	return _jn(n, &x);
}


/* ldexp */
#ifndef ARCH_ldexp
double ldexp(double x, int y)
{
	return ldexpl(x, y);
}
#endif


/* ldexpf */
#ifndef ARCH_ldexpf
float ldexpf(float x, int y)
{
	return ldexp(x, y);
}
#endif


#ifndef ARCH_ldexpl
# warning Unsupported platform: ldexpl() is not implemented
long double ldexpl(long double x, int y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* lgamma */
double lgamma(double x)
{
    register int  k = floor (x);
    long double   w;
    long double   y;
    long double   z;
   
    _signgam = 0;

    if ( k >= 7 )
        return _logfact (x-1);
       
    if ( k == x )
        switch (k) {
        case 1 :
        case 2 : return 0.000000000000000000000000000l;
        case 3 : return 0.693147180559945309432805516l;
        case 4 : return 1.791759469228055000858148560l;
        case 5 : return 3.178053830347945619723759592l;
        case 6 : return 4.787491742782045994244981560l;
        default: return 1./0.; /* ignore the gcc warning, this is intentional */
        }
       
    z = _logfact (y = x - k + 7.0 - 1);
    w = 1;
    for ( k = 7 - k; k--; )
        w *= y, y -= 1.;
       
    _signgam = k >= 0  ?  0  :  k & 1;
    return z - log (w);
}


#if 0
float lgammaf(float);
long double lgammal(long double);
long long llrint(double);
long long llrintf(float);
long long llrintl(long double);
long long llround(double);
long long llroundf(float);
long long llroundl(long double);
#endif


/* log */
#ifndef ARCH_log
double log(double x)
{
	return logl(x);
}
#endif


#if 0
double log10(double);
float log10f(float);
long double log10l(long double);
double log1p(double);
float log1pf(float);
long double log1pl(long double);
double log2(double);
float log2f(float);
long double log2l(long double);
double logb(double);
float logbf(float);
long double logbl(long double);
#endif


/* logf */
#ifndef ARCH_logf
float logf(float x)
{
	return log(x);
}
#endif


/* logl */
#ifndef ARCH_logl
# warning Unsupported platform: logl() is not implemented
long double logl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
long lrint(double);
long lrintf(float);
long lrintl(long double);
long lround(double);
long lroundf(float);
long lroundl(long double);
#endif


/* modf */
double modf(double x, double * iptr)
{
	double ret = fmod(x, 1.0);

	*iptr = x - ret;
	return ret;
}


#if 0
float modff(float, float *);
long double modfl(long double, long double *);
double nan(const char *);
float nanf(const char *);
long double nanl(const char *);
double nearbyint(double);
float nearbyintf(float);
long double nearbyintl(long double);
double nextafter(double, double);
float nextafterf(float, float);
long double nextafterl(long double, long double);
double nexttoward(double, long double);
float nexttowardf(float, long double);
long double nexttowardl(long double, long double);
#endif


/* pow */
#ifndef ARCH_pow
double pow(double x, double y)
{
	return powl(x, y);
}
#endif


#ifndef ARCH_powf
float powf(float x, float y)
{
	return pow(x, y);
}
#endif


#ifndef ARCH_powl
# warning Unsupported platform: powl() is not implemented
long double powl(long double x, long double y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
double remainder(double, double);
float remainderf(float, float);
long double remainderl(long double, long double);
double remquo(double, double, int *);
float remquof(float, float, int *);
long double remquol(long double, long double, int *);
#endif


/* rint */
double rint(double x)
{
	return floor(x + 0.5);
}


#if 0
float rintf(float);
long double rintl(long double);
#endif


/* round */
#ifndef ARCH_round
double round(double x)
{
	return roundl(x);
}
#endif


/* roundf */
#ifndef ARCH_roundf
float roundf(float x)
{
	return round(x);
}
#endif


/* roundl */
#ifndef ARCH_roundl
# warning Unsupported platform: roundl() is not implemented
long double roundl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
double scalb(double, double);
double scalbln(double, long);
float scalblnf(float, long);
long double scalblnl(long double, long);
double scalbn(double, int);
float scalbnf(float, int);
long double scalbnl(long double, int);
#endif


/* sin */
#ifndef ARCH_sin
double sin(double x)
{
	return sinl(x);
}
#endif


#ifndef ARCH_sinf
float sinf(float x)
{
	return sin(x);
}
#endif


#if 0
double sinh(double);
float sinhf(float);
long double sinhl(long double);
#endif


#ifndef ARCH_sinl
# warning Unsupported platform: sinl() is not implemented
long double sinl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* sqrt */
#ifndef ARCH_sqrt
double sqrt(double x)
{
	return sqrtl(x);
}
#endif


/* sqrtf */
#ifndef ARCH_sqrtf
float sqrtf(float x)
{
	return sqrt(x);
}
#endif


/* sqrtl */
#ifndef ARCH_sqrtl
# warning Unsupported platform: sqrtl() is not implemented
long double sqrtl(long double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* tan */
#ifndef ARCH_tan
double tan(double x)
{
	return sin(x) / cos(x);
}
#endif


/* tanf */
#ifndef ARCH_tanf
float tanf(float x)
{
	return tan(x);
}
#endif


#if 0
double tanh(double);
float tanhf(float);
long double tanhl(long double);
#endif


/* tanl */
#ifndef ARCH_tanl
long double tanl(long double x)
{
	return sinl(x) / cosl(x);
}
#endif


#if 0
double tgamma(double);
float tgammaf(float);
long double tgammal(long double);
double trunc(double);
float truncf(float);
long double truncl(long double);
#endif


/* y0 */
double y0(double x)
{
	return _yn(0, &x);
}


/* y1 */
double y1(double x)
{
	return _yn(1, &x);
}


/* yn */
double yn(int n, double x)
{
	return _yn(n, &x);
}
