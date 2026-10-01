#ifndef _WCHAR_H
#define _WCHAR_H

// Only encoding I'm willing to support is UTF-8,
// if you don't like that, shut up, or send patches

#include <stdio.h> // for FILE
#include <stdarg.h> // for va_list
#include <stddef.h> // for wchar_t, NULL
#include <stdint.h> // for WCHAR_MAX, WCHAR_MIN
#include <time.h> // for tm

typedef unsigned int wint_t;
// top 2 bits are the remaining characters for conversion
typedef wint_t mbstate_t;

#define WEOF 0xFFFFFFFFU

wint_t btowc(int c);
int wctob(wint_t c);
int fwide(FILE *stream, int mode);
wchar_t *wcpcpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2);
wchar_t *wcpncpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n);
wchar_t *wcscpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2);
wchar_t *wcsncpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n);
wchar_t *wcsdup(const wchar_t *string);
size_t wcslen(const wchar_t *ws);
size_t wcsnlen(const wchar_t *ws, size_t maxlen);
size_t wcsspn(const wchar_t *ws1, const wchar_t *ws2);
size_t wcscspn(const wchar_t *ws1, const wchar_t *ws2);
wchar_t *wcscat(wchar_t *__restrict ws1, const wchar_t *__restrict ws2);
wchar_t *wcsncat(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n);
wchar_t *wcschr(const wchar_t *ws, wchar_t wc);
wchar_t *wcsrchr(const wchar_t *ws, wchar_t wc);
wchar_t *wcspbrk(const wchar_t *ws1, const wchar_t *ws2);
wchar_t *wcsstr(const wchar_t *__restrict ws1, const wchar_t *__restrict ws2);
wchar_t *wmemchr(const wchar_t *ws, wchar_t wc, size_t n);
int wmemcmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);
wchar_t *wmemcpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n);
wchar_t *wmemmove(wchar_t *ws1, const wchar_t *ws2, size_t n);
wchar_t *wmemset(wchar_t *ws, wchar_t wc, size_t n);

int wcwidth(wchar_t wc); // source in wctype.c
int wcswidth(const wchar_t *pwcs, size_t n);
int wcscmp(const wchar_t *ws1, const wchar_t *ws2);
int wcsncmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);
int wcscoll(const wchar_t *ws1, const wchar_t *ws2);
int wcscasecmp(const wchar_t *ws1, const wchar_t *ws2);
int wcsncasecmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);

int mbsinit(const mbstate_t *ps);
size_t wcrtomb(char *__restrict s, wchar_t wc, mbstate_t *__restrict ps);
int wctomb(char *s, wchar_t wchar);
size_t mbrtowc(wchar_t *__restrict pwc, const char *__restrict s, size_t n, mbstate_t *__restrict ps);
size_t mbrlen(const char *__restrict s, size_t n, mbstate_t *__restrict ps);
size_t mbsrtowcs(wchar_t *__restrict dst, const char **__restrict src, size_t len, mbstate_t *__restrict ps);
size_t mbsnrtowcs(wchar_t *__restrict dst, const char **__restrict src, size_t nmc, size_t len, mbstate_t *__restrict ps);
size_t wcsrtombs(char *__restrict dst, const wchar_t **__restrict src, size_t len, mbstate_t *__restrict ps);
size_t wcsnrtombs(char *__restrict dst, const wchar_t **__restrict src, size_t nwc, size_t len, mbstate_t *__restrict ps);

wint_t fgetwc(FILE *stream);
wint_t getwc(FILE *stream);
wint_t getwchar();
wint_t fputwc(wchar_t wc, FILE *stream);
wint_t putwc(wchar_t wc, FILE *stream);
wint_t putwchar(wchar_t wc);
int fputws(const wchar_t *__restrict ws, FILE *__restrict stream);

wint_t ungetwc(wint_t wc, FILE *stream);
wchar_t *fgetws(wchar_t *__restrict ws, int n, FILE *__restrict stream);

// this is the dumbest thing ever, but until POSIX issue 7, all of these functions were here (OB XSI)
// and some software really does expect it here for some reason
#include <wctype.h>
#endif