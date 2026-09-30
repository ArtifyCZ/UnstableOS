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
size_t wcslen(const wchar_t *ws);
size_t wcsnlen(const wchar_t *ws, size_t maxlen);
wchar_t *wcscat(wchar_t *__restrict ws1, const wchar_t *__restrict ws2);
wchar_t *wcsncat(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n);
int wcscmp(const wchar_t *ws1, const wchar_t *ws2);
int wcsncmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);
int wcscasecmp(const wchar_t *ws1, const wchar_t *ws2);
int wcsncasecmp(const wchar_t *ws1, const wchar_t *ws2, size_t n);

int mbsinit(const mbstate_t *ps);
size_t wcrtomb(char *__restrict s, wchar_t wc, mbstate_t *__restrict ps);
int wctomb(char *s, wchar_t wchar);
size_t mbrtowc(wchar_t *__restrict pwc, const char *__restrict s, size_t n, mbstate_t *__restrict ps);
size_t mbrlen(const char *__restrict s, size_t n, mbstate_t *__restrict ps);

wint_t fgetwc(FILE *stream);
wint_t getwc(FILE *stream);
wint_t getwchar();
wint_t fputwc(wchar_t wc, FILE *stream);
wint_t putwc(wchar_t wc, FILE *stream);
wint_t putwchar(wchar_t wc);
int fputws(const wchar_t *__restrict ws, FILE *__restrict stream);

wint_t ungetwc(wint_t wc, FILE *stream);
wchar_t *fgetws(wchar_t *__restrict ws, int n, FILE *__restrict stream);
#endif