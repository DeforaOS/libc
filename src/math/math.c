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
/* XXX in part from dietlibc */



#include "sys/types.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
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
/* acos */
#ifndef ARCH_acos
double acos(double x)
{
	return acosl(x);
}
#endif


/* acosf */
#ifndef ARCH_acosf
float acosf(float x)
{
	return acos(x);
}
#endif


/* acosh */
#ifndef ARCH_acosh
double acosh(double x)
{
	return acoshl(x);
}
#endif


/* acoshf */
#ifndef ARCH_acoshf
float acoshf(float x)
{
	return acosh(x);
}
#endif


/* acoshl */
#ifndef ARCH_acoshl
# warning Unsupported platform: acoshl() is not implemented
long double acoshl(long double x)
{
	if(x < 1.0)
	{
		errno = EDOM;
		return nanl(NULL);
	}
	/* FIXME implement */
	return 0.0;
}
#endif


/* acosl */
#ifndef ARCH_acosl
# warning Unsupported platform: acosl() is not implemented
long double acosl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* asin */
#ifndef ARCH_asin
double asin(double x)
{
	return asinl(x);
}
#endif


/* asinf */
#ifndef ARCH_asinf
float asinf(float x)
{
	return asin(x);
}
#endif


/* asinh */
#ifndef ARCH_asinh
double asinh(double x)
{
	return asinhl(x);
}
#endif


/* asinhf */
#ifndef ARCH_asinhf
float asinhf(float x)
{
	return asinh(x);
}
#endif


/* asinhl */
#ifndef ARCH_asinhl
# warning Unsupported platform: asinhl() is not implemented
long double asinhl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* asinl */
#ifndef ARCH_asinl
# warning Unsupported platform: asinl() is not implemented
long double asinl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
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
	(void) x;
	(void) y;

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
	if(abs(x) >= 1.0)
	{
		errno = EDOM;
		return nanl(NULL);
	}
	/* FIXME implement */
	return 0.0;
}
#endif


/* atanl */
#ifndef ARCH_atanl
# warning Unsupported platform: atanl() is not implemented
long double atanl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif



/* cbrt */
#ifndef ARCH_cbrt
double cbrt(double x)
{
	return cbrtl(x);
}
#endif


/* cbrtf */
#ifndef ARCH_cbrtf
float cbrtf(float x)
{
	return cbrt(x);
}
#endif


/* cbrtl */
#ifndef ARCH_cbrtl
# warning Unsupported platform: cbrtl() is not implemented
long double cbrtl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
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

	y = roundl(x);
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
#ifndef ARCH_cosf
float cosf(float x)
{
	return cos(x);
}
#endif


/* cosh */
#ifndef ARCH_cosh
double cosh(double x)
{
	return (exp(x) + exp(-x)) / 2;
}
#endif


/* coshf */
#ifndef ARCH_coshf
float coshf(float x)
{
	return (expf(x) + expf(-x)) / 2;
}
#endif


/* coshl */
#ifndef ARCH_coshl
long double coshl(long double x)
{
	return (expl(x) + expl(-x)) / 2;
}
#endif


/* cosl */
#ifndef ARCH_cosl
# warning Unsupported platform: cosl() is not implemented
long double cosl(long double x)
{
	(void) x;

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


/* exp2 */
#ifndef ARCH_exp2
double exp2(double x)
{
	return exp2l(x);
}
#endif


/* exp2f */
#ifndef ARCH_exp2f
float exp2f(float x)
{
	return exp2(x);
}
#endif


/* exp2l */
#ifndef ARCH_exp2l
# warning Unsupported platform: exp2l() is not implemented
long double exp2l(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
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
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* expm1 */
#ifndef ARCH_expm1
double expm1(double x)
{
	return expm1l(x);
}
#endif


/* expm1f */
#ifndef ARCH_expm1f
float expm1f(float x)
{
	return expm1(x);
}
#endif


/* expm1l */
#ifndef ARCH_expm1l
# warning Unsupported platform: expm1l() is not implemented
long double expm1l(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
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


/* fdim */
#ifndef ARCH_fdim
double fdim(double x, double y)
{
	return fdiml(x, y);
}
#endif


/* fdimf */
#ifndef ARCH_fdimf
float fdimf(float x, float y)
{
	return fdim(x, y);
}
#endif


/* fdiml */
#ifndef ARCH_fdiml
# warning Unsupported platform: fdiml() is not implemented
long double fdiml(long double x, long double y)
{
	(void) x;
	(void) y;

	/* FIXME implement */
	return 0.0;
}
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

	y = roundl(x);
	return (y <= x) ? y : y - 1.0;
}
#endif


#if 0
double fma(double, double, double);
float fmaf(float, float, float);
long double fmal(long double, long double, long double);
#endif


/* fmax */
#ifndef ARCH_fmax
double fmax(double x, double y)
{
	if(isnan(x))
		return y;
	if(isnan(y))
		return x;
	return (x >= y) ? x : y;
}
#endif


/* fmaxf */
#ifndef ARCH_fmaxf
float fmaxf(float x, float y)
{
	if(isnan(x))
		return y;
	if(isnan(y))
		return x;
	return (x >= y) ? x : y;
}
#endif


/* fmaxl */
#ifndef ARCH_fmaxl
long double fmaxl(long double x, long double y)
{
	if(isnan(x))
		return y;
	if(isnan(y))
		return x;
	return (x >= y) ? x : y;
}
#endif


/* fmin */
#ifndef ARCH_fmin
double fmin(double x, double y)
{
	if(isnan(x))
		return y;
	if(isnan(y))
		return x;
	return (x <= y) ? x : y;
}
#endif


/* fminf */
#ifndef ARCH_fminf
float fminf(float x, float y)
{
	if(isnan(x))
		return y;
	if(isnan(y))
		return x;
	return (x <= y) ? x : y;
}
#endif


/* fminl */
#ifndef ARCH_fminl
long double fminl(long double x, long double y)
{
	if(isnan(x))
		return y;
	if(isnan(y))
		return x;
	return (x <= y) ? x : y;
}
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


/* fmodl */
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
double frexp(double x, int * y)
{
	return frexpl(x, y);
}
#endif


/* frexpf */
#ifndef ARCH_frexpf
float frexpf(float x, int * y)
{
	return frexp(x, y);
}
#endif


/* frexpl */
#ifndef ARCH_frexpl
# warning Unsupported platform: frexpl() is not implemented
long double frexpl(long double x, int * y)
{
	(void) x;
	(void) y;

	/* FIXME implement */
	return 0.0;
}
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
	(void) x;
	(void) y;

	/* XXX may overflow */
	return sqrt((x * x) + (y * y));
}
#endif


#if 0
int ilogb(double);
int ilogbf(float);
int ilogbl(long double);
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


/* ldexpl */
#ifndef ARCH_ldexpl
# warning Unsupported platform: ldexpl() is not implemented
long double ldexpl(long double x, int y)
{
	(void) x;
	(void) y;

	/* FIXME implement */
	return 0.0;
}
#endif


/* lgamma */
#ifndef ARCH_lgamma
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
#endif


/* lgammaf */
#ifndef ARCH_lgammaf
float lgammaf(float x)
{
	return lgamma(x);
}
#endif


/* lgammal */
#ifndef ARCH_lgammal
# warning Unsupported platform: lgammal() is not implemented
long double lgammal(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


#if 0
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


/* log10 */
#ifndef ARCH_log10
double log10(double x)
{
	return log10l(x);
}
#endif


/* log1p */
#ifndef ARCH_log1p
double log1p(double x)
{
	return log1pl(x);
}
#endif


/* log1pf */
#ifndef ARCH_log1pf
float log1pf(float x)
{
	return log1p(x);
}
#endif


/* log1pl */
#ifndef ARCH_log1pl
# warning Unsupported platform: log1pl() is not implemented
long double log1pl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* log2 */
#ifndef ARCH_log2
double log2(double x)
{
	return log2l(x);
}
#endif


/* log2f */
#ifndef ARCH_log2f
float log2f(float x)
{
	return log2(x);
}
#endif


/* log2l */
#ifndef ARCH_log2l
# warning Unsupported platform: log2l() is not implemented
long double log2l(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* logb */
#ifndef ARCH_logb
double logb(double x)
{
	return logbl(x);
}
#endif


/* logbf */
#ifndef ARCH_logbf
float logbf(float x)
{
	return logb(x);
}
#endif


/* logbl */
#ifndef ARCH_logbl
# warning Unsupported platform: logbl() is not implemented
long double logbl(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* log10f */
#ifndef ARCH_log10f
float log10f(float x)
{
	return log10(x);
}
#endif


/* log10l */
#ifndef ARCH_log10l
# warning Unsupported platform: log10l() is not implemented
long double log10l(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
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
	(void) x;

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
#ifndef ARCH_modf
double modf(double x, double * iptr)
{
	double ret = fmod(x, 1.0);

	*iptr = x - ret;
	return ret;
}
#endif


/* modff */
#ifndef ARCH_modff
float modff(float x, float * iptr)
{
	float ret = fmodf(x, 1.0);

	*iptr = x - ret;
	return ret;
}
#endif


/* modfl */
#ifndef ARCH_modfl
long double modfl(long double x, long double * iptr)
{
	long double ret = fmodl(x, 1.0);

	*iptr = x - ret;
	return ret;
}
#endif


/* nan */
double nan(const char * tagp)
{
	if(tagp == NULL || strlen(tagp) == 0)
		return strtod("NAN()", NULL);
	/* FIXME implement */
	return 0.0;
}


/* nanf */
float nanf(const char * tagp)
{
	if(tagp == NULL || strlen(tagp) == 0)
		return strtof("NAN()", NULL);
	/* FIXME implement */
	return 0.0;
}


/* nanl */
long double nanl(const char * tagp)
{
	if(tagp == NULL || strlen(tagp) == 0)
		return strtold("NAN()", NULL);
	/* FIXME implement */
	return 0.0;
}


#if 0
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


/* powf */
#ifndef ARCH_powf
float powf(float x, float y)
{
	return pow(x, y);
}
#endif


/* powl */
#ifndef ARCH_powl
long double powl(long double x, long double y)
{
	long double ret;

	if(x == 1.0 || y == 0.0)
		return 1.0;
	if(isnan(x))
		return x;
	else if(isnan(y))
		return y;
	if(x < 0.0 || roundl(y) != y)
	{
		/* XXX really report the error */
		errno = EDOM;
		return 0.0;
	}
	if(x == 0.0 && y > 0.0)
		return 0.0;
	/* XXX there are more corner cases with infinity */
	for(ret = 1.0; y >= 1.0; y -= 1.0)
		/* FIXME detect overflows and underflows */
		ret = ret * x;
	return ret;
}
#endif


/* remainder */
#ifndef ARCH_remainder
double remainder(double x, double y)
{
	return remainderl(x, y);
}
#endif


/* remainderf */
#ifndef ARCH_remainderf
float remainderf(float x, float y)
{
	return remainder(x, y);
}
#endif


/* remainderl */
#ifndef ARCH_remainderl
long double remainderl(long double x, long double y)
{
	return x - floor(x / y);
}
#endif


#if 0
double remquo(double, double, int *);
float remquof(float, float, int *);
long double remquol(long double, long double, int *);
#endif


/* rint */
#ifndef ARCH_rint
double rint(double x)
{
	return floor(x + 0.5);
}
#endif


/* rintf */
#ifndef ARCH_rintf
float rintf(float x)
{
	return floorf(x + 0.5);
}
#endif


/* rintl */
#ifndef ARCH_rintl
long double rintl(long double x)
{
	return floorl(x + 0.5);
}
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
	(void) x;

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


/* sinf */
#ifndef ARCH_sinf
float sinf(float x)
{
	return sin(x);
}
#endif


/* sinh */
#ifndef ARCH_sinh
double sinh(double x)
{
	return (exp(x) - exp(-x)) / 2;
}
#endif


/* sinhf */
#ifndef ARCH_sinhf
float sinhf(float x)
{
	return (expf(x) - expf(-x)) / 2;
}
#endif


/* sinhl */
#ifndef ARCH_sinhl
long double sinhl(long double x)
{
	return (expl(x) - expl(-x)) / 2;
}
#endif


/* sinl */
#ifndef ARCH_sinl
# warning Unsupported platform: sinl() is not implemented
long double sinl(long double x)
{
	(void) x;

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
	(void) x;

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
	return sinf(x) / cosf(x);
}
#endif


/* tanh */
#ifndef ARCH_tanh
double tanh(double x)
{
	return sinh(x) / cosh(x);
}
#endif


/* tanhf */
#ifndef ARCH_tanhf
float tanhf(float x)
{
	return sinhf(x) / coshf(x);
}
#endif


/* tanhl */
#ifndef ARCH_tanhl
long double tanhl(long double x)
{
	return sinhl(x) / coshl(x);
}
#endif


/* tanl */
#ifndef ARCH_tanl
long double tanl(long double x)
{
	return sinl(x) / cosl(x);
}
#endif


/* tgamma */
#ifndef ARCH_tgamma
double tgamma(double x)
{
	return tgammal(x);
}
#endif


/* tgammaf */
#ifndef ARCH_tgammaf
float tgammaf(float x)
{
	return tgamma(x);
}
#endif


/* tgammal */
#ifndef ARCH_tgammal
# warning Unsupported platform: tgammal() is not implemented
long double tgammal(long double x)
{
	(void) x;

	/* FIXME implement */
	return 0.0;
}
#endif


/* trunc */
#ifndef ARCH_trunc
double trunc(double x)
{
	return rint(x);
}
#endif


/* truncf */
#ifndef ARCH_truncf
float truncf(float x)
{
	return rintf(x);
}
#endif


/* truncl */
#ifndef ARCH_truncl
long double truncl(long double x)
{
	return rintl(x);
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
