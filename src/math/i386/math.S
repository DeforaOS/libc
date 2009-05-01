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



/* functions */
/* XXX math functions from dietlibc */
/* _flcetr */
.Lflcetr:
	xor	%ecx, %ecx
	mov	%ah, %ch
	push	%eax
	fstcw	(%esp)
	mov	(%esp), %ax
	and	$0x03, %ah
	or	%ecx, %eax
	mov	%ax, 0x02(%esp)
	fldcw	0x02(%esp)
	frndint
	fldcw	(%esp)
	pop	%eax
	ret


/* ceil */
.global ceil
.type ceil,@function
ceil:
	fldl	0x04(%esp)
	mov	$0x08, %ah
	jmp	.Lflcetr


/* cos */
.global cos
.type cos,@function
cos:
	fldl	0x04(%esp)
/* FIXME check there are no conflicts between labels 1, 2 and 3 and sin() */
1:	fcos
	fnstsw	%ax
	test	$0x04, %ah
	je	3f
	fldpi
	fadd	%st
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	test	$0x04, %ah
	jne	2b
	fstp	%st(1)
	fcos
3:	ret


/* exp */
.global exp
.type exp,@function
exp:
	fldl2e
	fmull	0x04(%esp)
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
	fldl	0x04(%esp)
	fabs
	ret


/* floor */
.global floor
.type floor,@function
floor:
	fldl	0x04(%esp)
	mov	$0x04, %ah
	jmp	.Lflcetr


/* fmod */
.global fmod
.type fmod,@function
fmod:
	fldl	0x0c(%esp)
	fldl	0x04(%esp)
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
	fldl	0x04(%esp)
	mov	0x0c(%esp), %eax
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
	fldl	0x0c(%esp)
	fldl	0x04(%esp)
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
	fildl	0x0c(%esp)
	fldl	0x04(%esp)
	fscale
	ret


/* log */
.global log
.type log,@function
log:
	fldln2
	fldl	0x04(%esp)
	fyl2x
	ret


/* pow */
.global pow
.type pow,@function
pow:
	fldl	0x04(%esp)
	fldl	0x0c(%esp)
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
#ifdef PIC
	jmp __finexp@PLT
#else
	jmp __finexp
#endif


/* sin */
.global sin
.type sin,@function
sin:
	fldl	0x04(%esp)
1:	fsin
	fnstsw	%ax
	test	$0x04, %ah
	je	3f
	fldpi
	fadd	%st
	fxch	%st(1)
2:	fprem1
	fnstsw	%ax
	test	$0x04, %ah
	jne	2b
	fstp	%st(1)
	fsin
3:	ret


/* sqrt */
.global sqrt
.type sqrt,@function
sqrt:
	fldl	0x04(%esp)
	fsqrt
	ret
