/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_TERMIOS_H
# define LIBC_KERNEL_NETBSD_TERMIOS_H

# define NCCS 20


/* types */
typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

struct termios
{
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[NCCS];
	int _padding[2];
};

#endif /* !LIBC_KERNEL_NETBSD_TERMIOS_H */
