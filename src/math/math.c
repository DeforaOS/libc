/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */
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
double atan(double);
#endif


double atan2(double x, double y)
{
	/* FIXME implement */
	return 0.0;
}


#if 0
float atan2f(float, float);
long double atan2l(long double, long double);
float atanf(float);
double atanh(double);
float atanhf(float);
long double atanhl(long double);
long double atanl(long double);
double cbrt(double);
float cbrtf(float);
long double cbrtl(long double);
double ceil(double);
float ceilf(float);
long double ceill(long double);
double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);
double cos(double);
float cosf(float);
double cosh(double);
float coshf(float);
long double coshl(long double);
long double cosl(long double);
double erf(double);
double erfc(double);
float erfcf(float);
long double erfcl(long double);
float erff(float);
long double erfl(long double);
double exp(double);
double exp2(double);
float exp2f(float);
long double exp2l(long double);
float expf(float);
long double expl(long double);
double expm1(double);
float expm1f(float);
long double expm1l(long double);
double fabs(double);
float fabsf(float);
long double fabsl(long double);
double fdim(double, double);
float fdimf(float, float);
long double fdiml(long double, long double);
double floor(double);
float floorf(float);
long double floorl(long double);
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
# warning Unsupported platform: fmod() is not implemented
double fmod(double x, double y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* fmod */
#ifndef ARCH_fmodf
# warning Unsupported platform: fmodf() is not implemented
float fmodf(float x, float y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
long double fmodl(long double, long double);
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
# warning Unsupported platform: hypot() is not implemented
double hypot(double x, double y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
float hypotf(float, float);
long double hypotl(long double, long double);
int ilogb(double);
int ilogbf(float);
int ilogbl(long double);
int isinf(float x);
int isnan(float x);
#endif


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
# warning Unsupported platform: ldexp() is not implemented
double ldexp(double x, int y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


/* ldexpf */
#ifndef ARCH_ldexpf
# warning Unsupported platform: ldexpf() is not implemented
float ldexpf(float x, int y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
long double ldexpl(long double, int);
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
# warning Unsupported platform: log() is not implemented
double log(double x)
{
	/* FIXME implement */
	return 0.0;
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
float logf(float);
long double logl(long double);
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
# warning Unsupported platform: pow() is not implemented
double pow(double x, double y)
{
	/* FIXME implement */
	return 0.0;
}
#endif


float powf(float x, float y)
{
	/* FIXME implement */
	return 0.0;
}


#if 0
long double powl(long double, long double);
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
double round(double);
float roundf(float);
long double roundl(long double);
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
# warning Unsupported platform: sin() is not implemented
double sin(double x)
{
	return 0.0;
}
#endif


#if 0
float sinf(float);
double sinh(double);
float sinhf(float);
long double sinhl(long double);
long double sinl(long double);
#endif


/* sqrt */
#ifndef ARCH_sqrt
# warning Unsupported platform: sqrt() is not implemented
double sqrt(double x)
{
	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
float sqrtf(float);
long double sqrtl(long double);
double tan(double);
float tanf(float);
double tanh(double);
float tanhf(float);
long double tanhl(long double);
long double tanl(long double);
double tgamma(double);
float tgammaf(float);
long double tgammal(long double);
double trunc(double);
float truncf(float);
long double truncl(long double);
#endif


/* FIXME place accordingly and compile conditionally */
/* ceil */
#ifndef ARCH_ceil
# warning Unsupported platform: ceil() is not implemented
double ceil(double x)
{
	return 0.0;
}
#endif


/* cos */
#ifndef ARCH_cos
# warning Unsupported platform: cos() is not implemented
double cos(double x)
{
	return 0.0;
}
#endif


/* exp */
#ifndef ARCH_exp
# warning Unsupported platform: exp() is not implemented
double exp(double x)
{
	return 0.0;
}
#endif


/* fabs */
#ifndef ARCH_fabs
# warning Unsupported platform: fabs() is not implemented
double fabs(double x)
{
	return 0.0;
}
#endif


/* floor */
#ifndef ARCH_floor
# warning Unsupported platform: floor() is not implemented
double floor(double x)
{
	return 0.0;
}
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
