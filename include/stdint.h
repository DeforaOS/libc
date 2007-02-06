/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_STDINT_H
# define LIBC_STDINT_H


/* types */
typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

# ifndef intptr_t
#  define intptr_t intptr_t
typedef signed long intptr_t;
# endif
# ifndef uintptr_t
#  define uintptr_t uintptr_t
typedef unsigned long uintptr_t;
# endif

#endif /* !LIBC_STDINT_H */
