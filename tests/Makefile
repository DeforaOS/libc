TARGETS	= includes setjmp signal start stdint tests.txt
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

start_OBJS = start.o
start_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
start_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

start: $(start_OBJS)
	$(CC) -o start $(start_OBJS) $(start_LDFLAGS)

stdint_OBJS = stdint.o
stdint_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
stdint_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

stdint: $(stdint_OBJS)
	$(CC) -o stdint $(stdint_OBJS) $(stdint_LDFLAGS)

tests.txt: includes setjmp signal start stdint
	./tests.sh -P "$(PREFIX)" -- "tests.txt"

includes.o: includes.c ../src/libc.a
	$(CC) $(includes_CFLAGS) -c includes.c

setjmp.o: setjmp.c ../include/setjmp.h ../src/setjmp.c
	$(CC) $(setjmp_CFLAGS) -c setjmp.c

signal.o: signal.c ../include/signal.h ../src/signal.c
	$(CC) $(signal_CFLAGS) -c signal.c

start.o: start.c
	$(CC) $(start_CFLAGS) -c start.c

stdint.o: stdint.c
	$(CC) $(stdint_CFLAGS) -c stdint.c

clean:
	$(RM) -- $(includes_OBJS) $(setjmp_OBJS) $(signal_OBJS) $(start_OBJS) $(stdint_OBJS) $(tests.txt_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
