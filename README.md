DeforaOS libc
=============

About DeforaOS libc
-------------------

This implementation of the standard C library has a number of goals:

 * remain simple while supporting as much of POSIX as possible;
 * getting rid of as much historical weight as likely;
 * support any combination of kernel, compiler or hardware architecture;
 * ease cross-compilation (including cross-OS) thanks to these portable headers;
 * ensure code compiling with this libc will build everywhere supported as-is;
 * generally, let headers and code be more readable to humans or programs.

Some of the most immediate benefits include faster compilation times, while
also reducing the storage footprint. It is also useful during the development of
programs intended to be portable across Operating Systems.

DeforaOS libc is part of the DeforaOS Project, and distributed under the terms
of the BSD 2-clause license.


Compiling DeforaOS libc
-----------------------

Simply running `make` with no argument should be enough to build DeforaOS libc
on your platform:

    $ make

The build process uses the default compiler available on the system (through
the `CC` variable). The compiler used can therefore be defined as follows:

    $ make CC="/path/to/the/compiler"

DeforaOS libc is developed with GCC as the main compiler.

To install DeforaOS libc in a dedicated directory, like `/path/to/libc`:

    $ make PREFIX="/path/to/libc" install

_Warning_: unless you know what you are doing, do not install DeforaOS libc in a
           directory where it might conflict with the system headers and
	   libraries, like `/usr` or even the default `/usr/local`.


Generating Makefiles
--------------------

Official releases of DeforaOS libc ship with Makefiles, fitting BSD Unix and
Linux-based platforms by default. The Makefiles are generated with the
`configure` tool from the DeforaOS configure Project, found at
<http://www.defora.org/os/project/16/configure>.

This tool is necessary to generate Makefiles for other platforms (including
MacOS X), or when working with development versions of DeforaOS libc.

The following command should be enough to re-generate the Makefiles:

    $ configure

Please refer to the documentation of DeforaOS configure for further
instructions.


Compiling programs against DeforaOS libc
----------------------------------------

The following instructions assume that DeforaOS libc is installed in the
`/path/to/libc` directory.

With GCC:

    $ make CPPFLAGS="-nostdinc -isystem /path/to/libc/include" \
      LDFLAGS="-nostdlib -L/path/to/libc/src -Wl,-rpath,/path/to/libc/src -lc /path/to/libc/src/start.o" \
      target


Cross-compiling with DeforaOS libc
----------------------------------

DeforaOS libc supports cross-compiling without any specific configuration.
Simply refer to the right compiler while building, as follows:

    $ make CC="/path/to/the/cross/compiler"

Compatibility with GCC's command-line syntax is assumed by default (for both
building and linking).

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
