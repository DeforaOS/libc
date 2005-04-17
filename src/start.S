/* start.S */



.text
.global _start
_start:
	pop	%ecx		/* argc */
	mov	%esp, %ebx	/* argv */
	mov	%esp, %eax	/* envp */
	add	$4, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	xor	%ebp, %ebp	/* stack */
	push	%ebp
	push	%ebp
	push	%ebp
	mov	%esp, %ebp
	push	%eax
	push	%ebx
	push	%ecx
	call	main
	call	exit
