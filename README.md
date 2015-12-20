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

libc is part of the DeforaOS Project, and distributed under the terms of the BSD
2-clause license.


Compiling libc
--------------

libc is developed with GCC as the main compiler.

Simply running `make` with no argument should be enough regardless:

    $ make

To install libc in a dedicated directory, like `/path/to/libc`:

    $ make PREFIX="/path/to/libc" install

_Warning_: unless you know what you are doing, do not install libc in a
           directory where it might conflict with the system headers and
	   libraries, like `/usr` or even the default `/usr/local`.


Compiling programs against libc
-------------------------------

The following instructions assume that libc is installed in the
`/path/to/libc` directory.

With GCC:

    $ make CPPFLAGS="-nostdinc -isystem /path/to/libc/include" \
        LDFLAGS="-nostdlib -L/path/to/libc/src -Wl,-rpath,/path/to/libc/src -lc /path/to/libc/src/start.o" \
        target


Cross-compiling with libc
-------------------------

It is sometimes possible to build cross-OS binaries thanks to DeforaOS libc,
without requiring a cross-compiler in the first place. For instance, to build a
Linux i386 binary on NetBSD amd64, with GCC:

Build DeforaOS libc as follows:

    $ make CC="gcc -m32 -Wl,--dynamic-linker,/lib/ld-linux.so.2" \
	CPPFLAGS="-U __NetBSD__ -D __linux__"

Build the target binary as follows:

    $ make CC="gcc -m32 -Wl,--dynamic-linker,/lib/ld-linux.so.2" \
	CPPFLAGS="-U __NetBSD__ -D __linux__ -nostdinc -isystem /path/to/libc/include" \
        LDFLAGS="-nostdlib -L/path/to/libc/src -Wl,-rpath,/path/to/libc/src -lc /path/to/libc/src/start.o" \
        target

This should provide a functional Linux/i386 binary.
