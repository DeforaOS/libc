TARGETS	= includes setjmp signal tests
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
CC	?= cc
CPPFLAGSF= -nostdinc -I ../include
CPPFLAGS?=
CFLAGSF	= -W
CFLAGS	= -Wall -g -O2 -ffreestanding
LDFLAGSF= -nostdlib -L ../src -Wl,-rpath,$(PWD)/../src -lc ../src/start.o
LDFLAGS	= `$(CC) -print-libgcc-file-name`
RM	?= rm -f
LN	?= ln -f
MKDIR	?= mkdir -p
INSTALL	?= install


all: $(TARGETS)

includes_OBJS = includes.o
includes_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
includes_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

includes: $(includes_OBJS)
	$(CC) -o includes $(includes_OBJS) $(includes_LDFLAGS)

setjmp_OBJS = setjmp.o
setjmp_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
setjmp_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

setjmp: $(setjmp_OBJS)
	$(CC) -o setjmp $(setjmp_OBJS) $(setjmp_LDFLAGS)

signal_OBJS = signal.o
signal_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
signal_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

signal: $(signal_OBJS)
	$(CC) -o signal $(signal_OBJS) $(signal_LDFLAGS)

tests: setjmp
	./tests.sh -P "$(PREFIX)" -- "tests"

includes.o: includes.c ../src/libc.so
	$(CC) $(includes_CFLAGS) -c includes.c

setjmp.o: setjmp.c ../include/setjmp.h ../src/setjmp.c
	$(CC) $(setjmp_CFLAGS) -c setjmp.c

signal.o: signal.c ../include/signal.h ../src/signal.c
	$(CC) $(signal_CFLAGS) -c signal.c

clean:
	$(RM) -- $(includes_OBJS) $(setjmp_OBJS) $(signal_OBJS) $(tests_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
