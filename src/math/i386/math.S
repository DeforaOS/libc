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



/* functions */
/* XXX math functions from dietlibc */
/* _flcetr */
.Lflcetr:
	xor	%ecx, %ecx
	mov	%ah, %ch
	push	%eax
	fstcw	(%esp)
	mov	(%esp), %ax
	and	$0x3, %ah
	or	%ecx, %eax
	mov	%ax, 0x2(%esp)
	fldcw	0x2(%esp)
	frndint
	fldcw	(%esp)
	pop	%eax
	ret


/* ceil */
.global ceil
.type ceil,@function
ceil:
	fldl	0x4(%esp)
	mov	$0x8, %ah
	jmp	.Lflcetr


/* cos */
.global cos
.type cos,@function
cos:
	fldl	0x4(%esp)
/* FIXME check there are no conflicts between labels 1, 2 and 3 and sin() */
1:	fcos
	fnstsw	%ax
	test	$0x4, %ah
	je	3f
	fldpi
	fadd	%st
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	test	$0x4, %ah
	jne	2b
	fstp	%st(1)
	fcos
3:	ret


/* exp */
.global exp
.type exp,@function
exp:
	fldl2e
	fmull	0x4(%esp)
__finexp:
	fst	%st(1)
	frndint
	fst	%st(2)
	fsubrp
	f2xm1
	fld1
	faddp
	fscale
	ret


/* fabs */
.global fabs
.type fabs,@function
fabs:
	fldl	0x4(%esp)
	fabs
	ret


/* fabsf */
.global fabsf
.type fabsf,@function
fabsf:
	flds	0x4(%esp)
	fabs
	ret


/* floor */
.global floor
.type floor,@function
floor:
	fldl	0x4(%esp)
	mov	$0x4, %ah
	jmp	.Lflcetr


/* fmod */
.global fmod
.type fmod,@function
fmod:
	fldl	0xc(%esp)
	fldl	0x4(%esp)
.Lfmod:
	fprem
	fstsw	%ax
	sahf
	jp	.Lfmod
	fstp	%st(1)
	ret


/* frexp */
.global frexp
.type frexp,@function
frexp:
	fldl	0x4(%esp)
	mov	0xc(%esp), %eax
	fxtract
	fxch
	fistpl	(%eax)
	push	0x3f000000	/* 1/2 */
	fmuls	(%esp)
	incl	(%eax)
	pop	%eax
	ret


/* hypot */
.global hypot
.type hypot,@function
hypot:
	fldl	0xc(%esp)
	fldl	0x4(%esp)
	fmul	%st(0), %st(0)
	fxch
	fmul	%st(0), %st(0)
	faddp
	fsqrt
	ret


/* ldexp */
.global ldexp
.type ldexp,@function
ldexp:
	fildl	0xc(%esp)
	fldl	0x4(%esp)
	fscale
	ret


/* log */
.global log
.type log,@function
log:
	fldln2
	fldl	0x4(%esp)
	fyl2x
	ret


/* pow */
.global pow
.type pow,@function
pow:
	fldl	0x4(%esp)
	fldl	0xc(%esp)
	ftst			/* y = 0 ? */
	fstsw	%ax
	fld1			/* st(0)=1, st(1)=y, st(2)=x */
	sahf
	jz	 1f		/* return 1 */
	fcomp	%st(1)		/* y = 1 ? */
	fstsw	%ax
	fxch			/* st(0)=x, st(1)=y */
	sahf
	jz	1f		/* return x */
	ftst			/* x = 0 ? */
	fstsw	%ax
	sahf
	jz	1f
	jnc	.Lfinpow	/* x > 0 */
	fxch			/* st(0)=y, st(1)=x */
	fld	%st(0)		/* st(0)=y, st(1)=y, st(2)=x */
	frndint			/* st(0)=int(y) */
	fcomp	%st(1)		/* y = int(y)? */
	fstsw	%ax
	fxch
	sahf
	jnz	.Lfinpow	/* fyl2x -> st(0) = NaN */
	/* y even or odd ? */
	fld1
	fadd	%st(0)		/* st(0) = 2 */
	fdivr	%st(2),%st(0)	/* st(0)=st(2)/2 */
	frndint
	fadd	%st(0),%st(0)
	fcomp	%st(2)		/* st(0) = x, st(1) = y */
	fstsw	%ax
	fchs			/* st(0) = -x */
	sahf
	jz	.Lfinpow	/* y even */
	call	.Lfinpow	/* y odd */
	fchs
1:	ret
.Lfinpow:
	fyl2x
#ifdef __PIC__
	jmp __finexp@PLT
#else
	jmp __finexp
#endif


/* sin */
.global sin
.type sin,@function
sin:
	fldl	0x4(%esp)
1:	fsin
	fnstsw	%ax
	test	$0x4, %ah
	je	3f
	fldpi
	fadd	%st
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	test	$0x4, %ah
	jne	2b
	fstp	%st(1)
	fsin
3:	ret


/* sinf */
.global sinf
.type sinf,@function
sinf:
	flds	0x4(%esp)
1:	fsin
	fnstsw	%ax
	test	$0x4, %ah
	je	3f
	fldpi
	fadd	%st
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	test	$0x4, %ah
	jne	2b
	fstp	%st(1)
	fsin
3:	ret


/* sqrt */
.global sqrt
.type sqrt,@function
sqrt:
	fldl	0x4(%esp)
	fsqrt
	ret


/* sqrtf */
.global sqrtf
.type sqrtf,@function
sqrtf:
	flds	0x4(%esp)
	fsqrt
	ret
