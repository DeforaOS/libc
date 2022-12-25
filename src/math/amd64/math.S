/* $Id$ */
/* Copyright (c) 2008-2020 Pierre Pronchery <khorben@defora.org> */
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



/* macros */
#ifdef __clang__
# ifndef MCALL1
#  define MCALL1(name, ins) \
.global name; \
name:; \
	movq	%xmm0, -0x8(%rsp); \
	fldl	-0x8(%rsp); \
	ins; \
	fstpl	-0x8(%rsp); \
	movq	-0x8(%rsp), %xmm0; \
	emms; \
	ret
# endif

# ifndef MCALL1L
#  define MCALL1L(name, ins) \
.global name; \
name:; \
	fldt	0x8(%rsp); \
	ins; \
	ret
# endif
#else
# ifndef MCALL1
#  define MCALL1(name, ins) \
.global name; \
.type name,@function; \
name:; \
	movq	%xmm0, -0x8(%rsp); \
	fldl	-0x8(%rsp); \
	ins; \
	fstpl	-0x8(%rsp); \
	movq	-0x8(%rsp), %xmm0; \
	emms; \
	ret
# endif

# ifndef MCALL1L
#  define MCALL1L(name, ins) \
.global name; \
.type name,@function; \
name:; \
	fldt	0x8(%rsp); \
	ins; \
	ret
# endif
#endif


/* functions */
/* atan */
.global atan
#ifndef __clang__
.type atan,@function
#endif
atan:
	movq	%xmm0, -0x8(%rsp)
	fldl	-0x8(%rsp)
	fld1
	fpatan
	fstpl	-0x8(%rsp)
	movq	-0x8(%rsp), %xmm0
	emms
	ret


/* atan2 */
.global atan2
#ifndef __clang__
.type atan2,@function
#endif
atan2:
	movq	%xmm0, -0x8(%rsp)
	movq	%xmm1, -0x10(%rsp)
	fldl	-0x8(%rsp)
	fldl	-0x10(%rsp)
	fpatan
	fstpl	-0x8(%rsp)
	movq	-0x8(%rsp), %xmm0
	emms
	ret


/* atan2l */
.global atan2l
#ifndef __clang__
.type atan2l,@function
#endif
atan2l:
	fldt	-0x10(%rsp)
	fldt	-0x8(%rsp)
	fpatan
	ret


/* atanl */
.global atanl
#ifndef __clang__
.type atanl,@function
#endif
atanl:
	fldt	0x8(%rsp)
	fld1
	fpatan
	ret


/* cos */
MCALL1(cos, fcos)


/* cosl */
MCALL1L(cosl, fcos)


/* fabs */
MCALL1(fabs, fabs)


/* fabsl */
MCALL1L(fabsl, fabs)


/* fmod */
.global fmod
#ifndef __clang__
.type fmod,@function
#endif
fmod:
	movq	%xmm1, -0x8(%rsp)
	fldl	-0x8(%rsp)
	movq	%xmm0, -0x8(%rsp)
	fldl	-0x8(%rsp)
.fmod_fprem:
	fprem
	fstsw	%ax
	sahf
	jp	.fmod_fprem
	fstpl	-0x8(%rsp)
	movq	-0x8(%rsp), %xmm0
	emms
	ret


/* fmodl */
.global fmodl
#ifndef __clang__
.type fmodl,@function
#endif
fmodl:
	fldt	0x18(%rsp)
	fldt	0x8(%rsp)
.fmodl_fprem:
	fprem
	fstsw	%ax
	sahf
	jp	.fmodl_fprem
	ret


/* round */
MCALL1(round, frndint)


/* roundl */
MCALL1L(roundl, frndint)


/* sin */
MCALL1(sin, fsin)


/* sinl */
MCALL1L(sinl, fsin)


/* sqrt */
MCALL1(sqrt, fsqrt)


/* sqrtl */
MCALL1L(sqrtl, fsqrt)


/* tan */
.global tan
#ifndef __clang__
.type tan,@function
#endif
tan:
	movq	%xmm0, -0x8(%rsp)
	fldl	-0x8(%rsp)
	fsincos
	fdivp	%st(0), %st(1)
	fstpl	-0x8(%rsp)
	movq	-0x8(%rsp), %xmm0
	emms
	ret


/* tanl */
.global tanl
#ifndef __clang__
.type tanl,@function
#endif
tanl:
	fldt	0x8(%rsp)
	fsincos
	fdivp	%st(0), %st(1)
	ret
