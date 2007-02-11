/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_TERMIOS_H
# define LIBC_TERMIOS_H

# include "compat/termios.h"


/* functions */
int tcgetattr(int fildes, struct termios * tp);

#endif /* !LIBC_TERMIOS_H */
