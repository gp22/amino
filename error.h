#ifndef _error_h
#define _error_h

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#define MAXLINE 4096 /* max text line length */

void err_quit(const char *, ...);
void err_sys(const char *, ...);

#endif
