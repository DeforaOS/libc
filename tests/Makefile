TARGETS	= includes regex select setjmp signal start stdint tests.txt
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
CC	?= cc
CPPFLAGSF= -nostdinc -isystem ../include -isystem ../include/rt
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

regex_OBJS = regex.o
regex_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
regex_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

regex: $(regex_OBJS)
	$(CC) -o regex $(regex_OBJS) $(regex_LDFLAGS)

select_OBJS = select.o
select_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
select_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

select: $(select_OBJS)
	$(CC) -o select $(select_OBJS) $(select_LDFLAGS)

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

tests.txt: includes regex setjmp signal start stdint
	./tests.sh -P "$(PREFIX)" -- "tests.txt"

includes.o: includes.c ../src/libc.a ../src/start.o
	$(CC) $(includes_CFLAGS) -c includes.c

regex.o: regex.c ../src/libc.a ../src/start.o
	$(CC) $(regex_CFLAGS) -c regex.c

select.o: select.c ../src/libc.a ../src/start.o
	$(CC) $(select_CFLAGS) -c select.c

setjmp.o: setjmp.c ../src/libc.a ../src/start.o
	$(CC) $(setjmp_CFLAGS) -c setjmp.c

signal.o: signal.c ../src/libc.a ../src/start.o
	$(CC) $(signal_CFLAGS) -c signal.c

start.o: start.c ../src/libc.a ../src/start.o
	$(CC) $(start_CFLAGS) -c start.c

stdint.o: stdint.c ../src/libc.a ../src/start.o
	$(CC) $(stdint_CFLAGS) -c stdint.c

clean:
	$(RM) -- $(includes_OBJS) $(regex_OBJS) $(select_OBJS) $(setjmp_OBJS) $(signal_OBJS) $(start_OBJS) $(stdint_OBJS) $(tests.txt_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
