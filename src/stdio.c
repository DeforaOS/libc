/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdarg.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "syscalls.h"
#include "stdio.h"

#define min(a, b) ((a) > (b) ? (b) : (a))


/* private */
/* types */
typedef enum _FILEDirection { FD_READ = 0, FD_WRITE = 1 } FILEDirection;

struct _FILE
{
	int fd;
	int flags;
	unsigned char _buf[BUFSIZ];
	unsigned char * buf;
	size_t bufsiz;
	size_t len;
	size_t pos;
	char eof;
	char error;
	int fbuf;
	FILEDirection dir;
};


/* prototypes */
static int _fopen_mode(char const * mode);
static FILE * _fopen_new(int fd, int flags, int fbuf);


/* public */
/* variables */
static FILE _stdin =
{
	STDIN_FILENO, O_RDONLY, { 0 }, _stdin._buf, sizeof(_stdin._buf), 0, 0,
	0, 0, _IOFBF, FD_READ
};
FILE * stdin = &_stdin;

static FILE _stdout =
{
	STDOUT_FILENO, O_WRONLY, { 0 }, _stdout._buf, sizeof(_stdout._buf), 0,
	0, 0, 0, _IOLBF, FD_WRITE
};
FILE * stdout = &_stdout;

static FILE _stderr =
{
	STDERR_FILENO, O_WRONLY, { 0 }, _stderr._buf, sizeof(_stderr._buf), 0,
	0, 0, 0, _IONBF, FD_WRITE
};
FILE * stderr = &_stderr;


/* functions */
/* clearerr */
void clearerr(FILE * file)
{
	file->eof = 0;
	file->error = 0;
}


/* ctermid */
char * ctermid(char * buf)
{
	static char const devtty[] = "/dev/tty";
	static char tty[L_ctermid];

	if(buf == NULL)
		buf = tty;
	snprintf(buf, L_ctermid, "%s", devtty);
	return buf;
}


/* fclose */
int fclose(FILE * file)
{
	int ret;
	
	ret = fflush(file);
	close(file->fd);
	free(file);
	return ret;
}


/* fdopen */
FILE * fdopen(int fd, char const * mode)
{
	return _fopen_new(fd, _fopen_mode(mode), isatty(fd) ? _IONBF : _IOFBF);
}


/* feof */
int feof(FILE * file)
{
	return file->eof;
}


/* ferror */
int ferror(FILE * file)
{
	return file->error;
}


/* fflush */
int fflush(FILE * file)
{
	ssize_t w;

	if(file == NULL)
	{
		errno = ENOSYS; /* FIXME implement */
		return -1;
	}
	if(file->dir == FD_READ)
	{
		file->len = 0;
		file->pos = 0;
		return 0;
	}
	else if(file->dir != FD_WRITE)
		return EOF;
	for(; file->pos < file->len; file->pos += w)
		if((w = write(file->fd, &file->buf[file->pos],
						file->len - file->pos)) < 0)
		{
			file->error = 1;
			return EOF;
		}
	file->pos = 0;
	file->len = 0;
	return 0;
}


/* fgetc */
int fgetc(FILE * file)
{
	unsigned char c;

	if(fread(&c, sizeof(c), 1, file) != 1)
		return EOF;
	return c;
}


/* fgets */
char * fgets(char * str, int size, FILE * fp)
{
	int i;
	int c;

	if(size < 0)
	{
		errno = EINVAL;
		return NULL;
	}
	for(i = 0; i + 1 < size; i++)
	{
		if((c = fgetc(fp)) == EOF)
		{
			if(i == 0 || !feof(fp))
				return NULL;
			break;
		}
		str[i] = c;
		if(c == '\n')
			break;
	}
	if(++i >= size)
		return NULL;
	str[i] = '\0';
	return str;
}


/* fileno */
int fileno(FILE * file)
{
	if(file == NULL)
	{
		errno = EBADF;
		return -1;
	}
	return file->fd;
}


/* flock */
void flockfile(FILE * file)
{
	struct flock fl;

	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = 0;
	fl.l_type = F_RDLCK | F_WRLCK;
	fl.l_whence = SEEK_SET;
	fcntl(file->fd, F_SETLKW, &fl);
}


/* fopen */
FILE * fopen(char const * path, char const * mode)
{
	FILE * file;
	int flags;
	int fd;

	if((flags = _fopen_mode(mode)) == -1
			|| (fd = open(path, flags, 0777)) < 0)
		return NULL;
	if((file = _fopen_new(fd, flags, isatty(fd) ? _IONBF : _IOFBF)) == NULL)
	{
		close(fd);
		return NULL;
	}
	return file;
}


/* fprintf */
int fprintf(FILE * file, char const * format, ...)
{
	int ret;
	va_list arg;

	va_start(arg, format);
	ret = vfprintf(file, format, arg);
	va_end(arg);
	return ret;
}


/* fputc */
int fputc(int c, FILE * file)
{
	unsigned char p = c;

	if(fwrite(&p, sizeof(char), 1, file) != 1)
		return EOF;
	return p;
}


/* fputs */
int fputs(char const * str, FILE * file)
{
	size_t len;

	if((len = strlen(str)) == 0)
		return 0;
	return fwrite(str, sizeof(char), len, file) == len ? 0 : EOF;
}


/* fread */
size_t fread(void * ptr, size_t size, size_t nb, FILE * file)
{
	char * p = (char*)ptr;
	size_t i;
	size_t j;
	size_t len;
	ssize_t r;

	if(file->dir != FD_READ)
	{
		if(fflush(file) != 0)
			return 0;
		else
			file->dir = FD_READ;
	}
	for(i = 0; i < nb; i++)
		for(j = 0; j < size; j += len)
		{
			if(file->pos == file->len)
			{
				if((r = read(file->fd, file->buf, file->bufsiz))
						< 0)
				{
					file->error = 1;
					return i;
				}
				else if(r == 0)
				{
					file->eof = 1;
					return i;
				}
				file->pos = 0;
				file->len = r;
			}
			len = min(file->len - file->pos, size - j);
			memcpy(p, &file->buf[file->pos], len);
			file->pos += len;
			p += len;
		}
	return i;
}


/* freopen */
FILE * freopen(char const * path, char const * mode, FILE * file)
{
	int flags;

	fflush(file);
	if(path == NULL)
	{
		if((flags = _fopen_mode(mode)) == -1)
		{
			if(fcntl(file->fd, F_SETFL, flags) == -1)
				return NULL;
			file->flags = flags;
			file->dir = flags & O_WRONLY ? FD_WRITE : FD_READ;
			return file;
		}
	}
	close(file->fd);
	clearerr(file);
	if((flags = _fopen_mode(mode)) == -1
			|| (file->fd = open(path, file->flags, 0777)) < 0)
		return NULL;
	file->flags = flags;
	file->dir = flags & O_WRONLY ? FD_WRITE : FD_READ;
	file->fbuf = isatty(file->fd) ? _IONBF : _IOFBF;
	return file;
}


/* fscanf */
int fscanf(FILE * fp, char const * format, ...)
{
	int ret;
	va_list arg;

	va_start(arg, format);
	ret = vfscanf(fp, format, arg);
	va_end(arg);
	return ret;
}


/* fseek */
int fseek(FILE * file, long offset, int whence)
{
	return fseeko(file, offset, whence);
}


/* fseeko */
int fseeko(FILE * file, off_t offset, int whence)
{
	if(whence != SEEK_CUR && whence != SEEK_END && whence != SEEK_SET)
	{
		errno = EINVAL;
		return -1;
	}
	if(fflush(file) != 0)
		return -1;
	return (lseek(file->fd, offset, whence)) != -1 ? 0 : -1;
}


/* ftell */
long ftell(FILE * file)
{
	long ret;

	if((ret = lseek(file->fd, SEEK_CUR, 0)) < 0)
		return -1;
	/* FIXME not tested */
	return ret - file->len + file->pos;
}


/* ftrylock */
int ftrylock(FILE * file)
{
	struct flock fl;

	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = 0;
	fl.l_type = F_RDLCK | F_WRLCK;
	fl.l_whence = SEEK_SET;
	return fcntl(file->fd, F_SETLK, &fl);
}


/* funlockfile */
void funlockfile(FILE * file)
{
	struct flock fl;

	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = 0;
	fl.l_type = F_UNLCK;
	fl.l_whence = SEEK_SET;
	fcntl(file->fd, F_SETLKW, &fl);
}


/* fwrite */
size_t fwrite(void const * ptr, size_t size, size_t nb, FILE * file)
{
	char const * p = (char const *)ptr;
	size_t i;
	size_t j;
	size_t len;
	ssize_t w;
	size_t x;

	if(file->dir != FD_WRITE)
	{
		if(fflush(file) != 0)
			return 0;
		file->dir = FD_WRITE;
	}
	for(i = 0; i < nb; i++)
		for(j = 0; j < size; j+=len)
		{
			len = min(file->bufsiz - file->len, size - j);
			memcpy(&file->buf[file->len], p, len);
			p += len;
			file->len += len;
			if(file->len != file->bufsiz) /* buffer is not full */
				continue;
			x = file->bufsiz - file->pos;
			if((w = write(file->fd, &file->buf[file->pos], x)) < 0)
			{
				file->error = 1;
				return i;
			}
			if((size_t)w != x) /* XXX cast */
				file->pos = w; /* buffer is not empty */
			else /* buffer is empty */
			{
				file->pos = 0;
				file->len = 0;
			}
		}
	if(file->fbuf == _IOFBF) /* fully buffered */
		return nb;
	if(file->fbuf == _IOLBF) /* line buffered */
		for(j = file->len; j > file->pos; j--)
		{
			if(file->buf[j - 1] == '\n')
				break;
		}
	else /* unbuffered */
		j = file->len;
	for(; file->pos < j; file->pos += w) /* empty buffer if necessary */
		if((w = write(file->fd, &file->buf[file->pos], j - file->pos))
				< 0)
		{
			file->error = 1;
			break; /* XXX should we otherwise report the error? */
		}
	return nb;
}


/* getc */
int getc(FILE * file)
{
	return fgetc(file);
}


/* getchar */
int getchar(void)
{
	return fgetc(stdin);
}


/* pclose */
int pclose(FILE * stream)
{
	return fclose(stream);
}


/* perror */
void perror(char const * s)
{
	if(s != NULL && *s != '\0')
		fprintf(stderr, "%s%s", s, ": ");
	/* strerror() never returns NULL */
	fputs(strerror(errno), stderr);
	fputc('\n', stderr);
}


/* popen */
static void _popen_child(char const * command, int flags, int * fd);

FILE * popen(char const * command, char const * mode)
{
	int flags;
	pid_t pid;
	int fd[2];

	if((flags = _fopen_mode(mode)) == -1)
		return NULL;
	if(pipe(fd) != 0)
		return NULL;
	if((pid = fork()) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return NULL;
	}
	if(pid == 0) /* child */
		_popen_child(command, flags, fd);
	if(flags & O_WRONLY)
		close(fd[0]);
	else
		close(fd[1]);
	return _fopen_new(flags & O_WRONLY ? fd[1] : fd[0], flags, _IONBF);
}

static void _popen_child(char const * command, int flags, int * fd)
{
	if(flags & O_WRONLY)
	{
		close(fd[1]);
		if(dup2(fd[0], 0) == -1)
			exit(127);
	}
	else
	{
		close(fd[0]);
		if(dup2(fd[1], 1) == -1)
			exit(127);
	}
	execlp("/bin/sh", "sh", "-c", command, NULL);
	exit(127);
}


/* printf */
int printf(char const * format, ...)
{
	int ret;
	va_list arg;

	va_start(arg, format);
	ret = vfprintf(stdout, format, arg);
	va_end(arg);
	return ret;
}


/* putc */
int putc(int c, FILE * fp)
{
	return fputc(c, fp);
}


/* putchar */
int putchar(int c)
{
	return fputc(c, stdout);
}


/* puts */
int puts(char const * string)
{
	size_t i;
	
	i = strlen(string);
	if(fwrite(string, sizeof(char), i, stdout) != i)
		return EOF;
	fputc('\n', stdout);
	return i <= INT_MAX ? i : INT_MAX;
}


/* remove */
int remove(char const * path)
{
	if(unlink(path) == 0)
		return 0;
	if(errno == EISDIR && rmdir(path) == 0)
		return 0;
	return -1;
}


/* rename */
#ifndef SYS_rename
# warning Unsupported platform: rename() is missing
int rename(char const * from, char const * to)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* rewind */
void rewind(FILE * file)
{
	if(fseek(file, 0, SEEK_SET) == 0)
		clearerr(file);
}


/* scanf */
int scanf(char const * format, ...)
{
	int ret;
	va_list arg;

	va_start(arg, format);
	ret = vfscanf(stdin, format, arg);
	va_end(arg);
	return ret;
}


/* setbuf */
void setbuf(FILE * file, char * buf)
{
	setvbuf(file, buf, (buf != NULL) ? _IOFBF : _IONBF, BUFSIZ);
}


/* setvbuf */
int setvbuf(FILE * file, char * buf, int type, size_t size)
{
	if(file->fd < 0 || file->len > 0)
	{
		errno = EBADF;
		return -1;
	}
	file->buf = (unsigned char *)buf;
	file->fbuf = type;
	file->bufsiz = size;
	return 0;
}


/* snprintf */
int snprintf(char * str, size_t size, char const * format, ...)
{
	va_list arg;
	int ret;

	va_start(arg, format);
	ret = vsnprintf(str, size, format, arg);
	va_end(arg);
	return ret;
}


/* sprintf */
int sprintf(char * str, char const * format, ...)
{
	va_list arg;
	int ret;

	va_start(arg, format);
	ret = vsprintf(str, format, arg);
	va_end(arg);
	return ret;
}


/* sscanf */
int sscanf(char const * string, char const * format, ...)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* tmpfile */
FILE * tmpfile(void)
{
	char * path;
	int fd;
	FILE * fp;

	if((path = mktemp("/tmp/tmp.XXXXXX")) == NULL)
		return NULL;
	if((fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0666)) < 0)
		return NULL;
	if(unlink(path) != 0
			|| (fp = fdopen(fd, "w+")) == NULL)
	{
		close(fd);
		return NULL;
	}
	return fp;
}


/* ungetc */
int ungetc(int c, FILE * file)
{
	if(c == EOF || c < 0)
	{
		errno = EINVAL;
		return EOF;
	}
	if(file->len == sizeof(file->buf))
	{
		errno = ENOBUFS;
		return EOF;
	}
	memmove(&file->buf[file->pos + 1], &file->buf[file->pos], file->len
			- file->pos);
	file->buf[file->pos] = c; /* XXX c may be silently truncated */
	file->len++;
	return file->buf[file->pos];
}


/* vfprintf */
typedef int (*print_func)(void * dest, size_t size, const char * buf);
static int _fprint(void * dest, size_t size, const char * buf);
static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg);

int vfprintf(FILE * file, char const * format, va_list arg)
{
	return _vprintf(_fprint, file, ~0, format, arg);
}

static int _fprint(void * dest, size_t size, char const buf[])
{
	FILE * fp = dest;

	return (fwrite(buf, sizeof(char), size, fp) == size) ? 0 : -1;
}

/* _vprintf */
typedef struct _print_args
{
	int ret;
	int flags;
	size_t width;
	size_t precision;
	int shrt;
	print_func func;
	void * dest;
	size_t * size;
} print_args;
static int _vfprintf_do(print_args * args, char const * buf, size_t len);
static int _vfprintf_do_do(print_args * args, char const * buf, size_t len);
#define FLAGS_HASH	0x01
#define FLAGS_MINUS	0x02
#define FLAGS_PLUS	0x04
#define FLAGS_SPACE	0x08
#define FLAGS_ZERO	0x10
static int _vprintf_flags(char const * p, size_t * i);
static size_t _vprintf_width(char const * p, size_t * i);
static size_t _vprintf_precision(char const * p, size_t * i);
static void _format_lutoa(char * dest, unsigned long n, size_t base, int upper);
static int _format_c(print_args * args, char const * chrp);
static int _format_d(print_args * args, long long * ptr);
static int _format_o(print_args * args, unsigned long long * ptr);
static int _format_s(print_args * args, char const * str);
static int _format_p(print_args * args, void * ptr);
static int _format_u(print_args * args, unsigned long long * ptr);
static int _format_x(print_args * args, unsigned long long * ptr, int upper);

static int _vprintf(print_func func, void * dest, size_t size,
		char const * format, va_list arg)
{
	print_args args;
	char const * p;		/* pointer to current format character */
	size_t i;
	int lng;
	int f = 0;
	char c;
	char const * str;
	long long int d;
	unsigned long long int u;
	void * ptr;

	args.ret = 0;
	args.func = func;
	args.dest = dest;
	args.size = &size;
	for(p = format; *p != '\0'; p += i)
	{
		args.flags = 0;
		args.width = 0;
		args.precision = 0;
		args.shrt = 0;
		for(i = 0; p[i] != '\0' && p[i] != '%'; i++);
		if(i > 0 && _vfprintf_do(&args, p, i) != 0)
			return -1;
		if(p[i++] != '%')
			break;
		if(p[i] == '%')
		{
			if(_vfprintf_do(&args, p++, 1) != 0)
				return -1;
			continue;
		}
		args.flags = _vprintf_flags(p, &i);
		args.width = _vprintf_width(p, &i);
		args.precision = _vprintf_precision(p, &i);
		for(lng = 0; p[i] != '\0'; i++)
		{
			if(p[i] == 'l')
			{
				if(++lng > 2)
				{
					errno = EINVAL;
					return -1;
				}
			}
			else if(p[i] == 'c')
			{
				c = va_arg(arg, int);
				f = _format_c(&args, &c);
				break;
			}
			else if(p[i] == 'd')
			{
				if(lng > 1)
					d = va_arg(arg, long long int);
				else if(lng == 1)
					d = va_arg(arg, long int);
				else
					d = va_arg(arg, int);
				f = _format_d(&args, &d);
				break;
			}
			else if(p[i] == 'h')
			{
				if(++args.shrt > 2)
				{
					errno = EINVAL;
					return -1;
				}
			}
			else if(p[i] == 'o')
			{
				if(lng > 1)
					u = va_arg(arg, unsigned long long int);
				else if(lng == 1)
					u = va_arg(arg, unsigned long int);
				else
					u = va_arg(arg, unsigned int);
				f = _format_o(&args, &u);
				break;
			}
			else if(p[i] == 'p')
			{
				ptr = va_arg(arg, void *);
				f = _format_p(&args, ptr);
				break;
			}
			else if(p[i] == 's')
			{
				str = va_arg(arg, char const *);
				f = _format_s(&args, str);
				break;
			}
			else if(p[i] == 'u')
			{
				if(lng > 1)
					u = va_arg(arg, unsigned long long int);
				else if(lng == 1)
					u = va_arg(arg, unsigned long int);
				else
					u = va_arg(arg, unsigned int);
				f = _format_u(&args, &u);
				break;
			}
			else if(p[i] == 'x' || p[i] == 'X')
			{
				if(lng > 1)
					u = va_arg(arg, unsigned long long int);
				else if(lng == 1)
					u = va_arg(arg, unsigned long int);
				else
					u = va_arg(arg,	unsigned int);
				f = _format_x(&args, &u, (p[i] == 'X'));
				break;
			}
			else if(p[i] == 'z')
			{
				if(lng != 0)
				{
					errno = EINVAL;
					return -1;
				}
				lng = 1;
			}
			else
			{
				errno = EINVAL;
				return -1;
			}
		}
		if(f != 0)
			return -1;
		i++;
	}
	return args.ret;
}

static int _vfprintf_do(print_args * args, char const * buf, size_t len)
{
	size_t i;
	char padding = ' ';

	if(args->flags & FLAGS_MINUS)
	{
		_vfprintf_do_do(args, buf, len);
		for(i = len; i < args->width; i++)
			if(_vfprintf_do_do(args, &padding, 1) != 0)
				return -1;
		return 0;
	}
	if(args->flags & FLAGS_ZERO)
		padding = '0';
	for(i = len; i < args->width; i++)
		if(_vfprintf_do_do(args, &padding, 1) != 0)
			return -1;
	return _vfprintf_do_do(args, buf, len);
}

static int _vfprintf_do_do(print_args * args, char const * buf, size_t len)
{
	size_t s;

	s = min(*(args->size), len);
	if(args->func(args->dest, s, buf) != 0)
		return -1;
	if((size_t)INT_MAX - len < (size_t)(args->ret))
	{
		errno = ERANGE;
		return -1;
	}
	*(args->size) -= s;
	args->ret += len;
	return 0;
}

static int _vprintf_flags(char const * p, size_t * i)
{
	int flags;

	for(flags = 0; p[*i] != '\0'; (*i)++)
	{
		if(p[*i] == '#')
			flags |= FLAGS_HASH;
		else if(p[*i] == '-')
			flags |= FLAGS_MINUS;
		else if(p[*i] == '+')
			flags |= FLAGS_PLUS;
		else if(p[*i] == ' ')
			flags |= FLAGS_SPACE;
		else if(p[*i] == '0')
			flags |= FLAGS_ZERO;
		else
			break;
	}
	return flags;
}

static size_t _vprintf_width(char const * p, size_t * i)
{
	size_t width;

	for(width = 0; p[*i] != '\0'; (*i)++)
	{
		if(p[*i] < '0' || p[*i] > '9')
			break;
		width *= 10;
		width += p[*i] - '0';
	}
	return width;
}

static size_t _vprintf_precision(char const * p, size_t * i)
{
	if(p[*i] != '.')
		return 0;
	(*i)++;
	return _vprintf_width(p, i);
}

static int _format_c(print_args * args, char const * chrp)
{
	return _vfprintf_do(args, chrp, sizeof(*chrp));
}

static int _format_d(print_args * args, long long * ptr)
{
	unsigned long long uval;

	if(*ptr >= 0)
	{
		uval = *ptr;
		return _format_u(args, &uval);
	}
	uval = -(*ptr);
	if(_vfprintf_do(args, "-", 1) != 0 || _format_u(args, &uval) != 0)
		return -1;
	return 0;
}

static int _format_o(print_args * args, unsigned long long * ptr)
{
	char tmp[22] = "";

	_format_lutoa(tmp, *ptr, 8, 0); /* XXX assumes tmp is large enough */
	return _vfprintf_do(args, tmp, strlen(tmp));
}

static int _format_s(print_args * args, char const * str)
{
	if(str == NULL) /* XXX be nice and don't crash */
		str = "(null)";
	return _vfprintf_do(args, str, strlen(str));
}

static int _format_p(print_args * args, void * ptr)
{
	char tmp[3 + sizeof(void*) + sizeof(void*)] = "0x";

	_format_lutoa(&tmp[2], (long)ptr, 16, 0); /* XXX cast */
	return _vfprintf_do(args, tmp, strlen(tmp));
}

static int _format_u(print_args * args, unsigned long long * ptr)
{
	char tmp[19] = "";

	_format_lutoa(tmp, *ptr, 10, 0); /* XXX assumes tmp is large enough */
	return _vfprintf_do(args, tmp, strlen(tmp));
}

static int _format_x(print_args * args, unsigned long long * ptr, int upper)
{
	unsigned long u = *ptr;
	char tmp[sizeof(long) + sizeof(long) + 1] = "";

	if(args->shrt == 1)
		u = u & 0xffff;
	else if(args->shrt == 2)
		u = u & 0xff;
	_format_lutoa(tmp, u, 16, upper); /* XXX assumes tmp large enough */
	if((args->flags & FLAGS_HASH) == FLAGS_HASH)
		if(_vfprintf_do_do(args, "0x", 2) != 0)
			return -1;
	return _vfprintf_do(args, tmp, strlen(tmp));
}

/* PRE	dest is long enough
 * POST	2 <= base <= 36		dest is the ascii representation of n
 *	else			dest is an empty string */
static void _format_lutoa(char * dest, unsigned long n, size_t base, int upper)
{
	static char const convl[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	static char const convu[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char const * conv = (upper != 0) ? convu : convl;
	size_t len = 0;
	unsigned long p;
	size_t i;

	if(base < 2 || base >= sizeof(convl))
	{
		dest[0] = '\0';
		return;
	}
	if(n == 0)
	{
		strcpy(dest, "0");
		return;
	}
	/* XXX performing twice the divisions is not optimal */
	for(p = n; p > 0; p /= base)
		len++;
	for(i = len; n > 0; n /= base)
	{
		p = n % base;
		dest[--i] = conv[p];
		n -= p;
	}
	dest[len] = '\0';
}


/* vfscanf */
int vfscanf(FILE * file, char const * format, va_list arg)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* vprintf */
int vprintf(char const * format, va_list arg)
{
	return _vprintf(_fprint, stdout, ~0, format, arg);
}


/* vsnprintf */
static int _sprint(void * dest, size_t size, const char * buf);

int vsnprintf(char * str, size_t size, char const * format, va_list arg)
{
	int ret;
	char * p = str;
	size_t i;

	if((ret = _vprintf(_sprint, &p, size, format, arg)) < 0)
		return ret;
	i = ret;
	if(i < size)
		str[ret] = '\0';
	else if(size > 0)
		str[size - 1] = '\0';
	return ret;
}

static int _sprint(void * dest, size_t size, char const buf[])
{
	char ** str = dest;

	if(*str == NULL || size == 0)
		return 0;
	strncpy(*str, buf, size);
	*str += size;
	return 0;
}


/* vsprintf */
int vsprintf(char * str, char const * format, va_list arg)
{
	int ret;
	char * p = str;
	size_t size = -1;

	if((ret = _vprintf(_sprint, &p, size, format, arg)) < 0)
		return ret;
	str[ret] = '\0';
	return ret;
}


/* private */
/* functions */
/* fopen_mode */
/* PRE
 * POST
 * 	-1	error
 * 	else	corresponding mode */
static int _fopen_mode(char const * mode)
{
	int flags;

	if(*mode == 'r')
	{
		flags = O_RDONLY;
		if(*++mode == 'b')
			++mode;
		if(*mode == '\0')
			return flags;
		if(*mode == '+' && ++mode)
			flags = O_RDWR;
	}
	else if(*mode == 'w')
	{
		flags = O_WRONLY | O_CREAT;
		if(*++mode == 'b')
			++mode;
		if(*mode == '\0')
			return flags;
		if(*mode == '+' && ++mode)
			flags = O_RDWR | O_CREAT;
	}
	else if(*mode == 'a')
	{
		flags = O_APPEND;
		if(*++mode == 'b')
			++mode;
		if(*mode == '\0')
			return flags;
		if(*mode == '+' && ++mode)
			flags |= O_CREAT;
	}
	else
	{
		errno = EINVAL;
		return -1;
	}
	if(*mode == 'b')
		++mode;
	if(*mode != '\0')
	{
		errno = EINVAL;
		return -1;
	}
	return flags;
}


/* fopen_new */
static FILE * _fopen_new(int fd, int flags, int fbuf)
{
	FILE * file;

	if(flags == -1)
		return NULL;
	if((file = malloc(sizeof(*file))) == NULL)
		return NULL;
	file->flags = flags;
	file->buf = file->_buf;
	file->bufsiz = sizeof(file->_buf);
	file->fd = fd;
	file->len = 0;
	file->pos = 0;
	file->eof = 0;
	file->error = 0;
	file->dir = file->flags & O_WRONLY ? FD_WRITE : FD_READ;
	file->fbuf = fbuf;
	return file;
}
