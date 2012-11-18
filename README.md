DeforaOS libc
=============

About libc
----------

This implementation of the standard C library has a number of goals:

 * remain simple while supporting as much of POSIX as possible;
 * getting rid of as much historical weight as likely;
 * support any combination of kernel, compiler or hardware architecture;
 * ease cross-compilation (including cross-OS) thanks to these portable headers;
 * ensure that code compiling with libc will build everywhere supported as-is;
 * generally, let headers and code be more readable to humans or programs.

Some of the most immediate benefits include faster compilation times, while
also reducing the storage footprint. It is also useful during the development of
programs intended to be portable across Operating Systems.

libc is part of the DeforaOS Project, and distributed under the terms of the
GNU General Public License, version 3 (GPLv3).


Compiling libc
--------------

With GCC, this should be enough:

    $ make

To install libc in a dedicated directory, like `/path/to/libc`:

    $ make PREFIX="/path/to/libc" install

_Warning_: unless you know what you are doing, do not install libc in a
           directory where it might conflict with your system's default headers
           and libraries, like `/usr` or even the default `/usr/local`.


Compiling programs against libc
-------------------------------

The following instructions assume that libc is installed in the
`/path/to/libc` directory.

With GCC:

    $ make CPPFLAGS="-nostdinc -isystem /path/to/libc/include" \
        LDFLAGS="-nostdlib -L/path/to/libc/src -Wl,-rpath,/path/to/libc/src -lc /path/to/libc/src/start.o" \
        target