#include <wchar.h>
#include <stdlib.h>


wint_t btowc(int c) {
    return c < 128 ? (int)(unsigned char)c : WEOF;
}

int wctob(wint_t c) {
    return c < 128 ? (int)(unsigned char)c : EOF;
}

int mbsinit(const mbstate_t *ps) {
    if (!ps || !*ps)
        return 1;
    return 0;
}

int fwide(FILE *stream, int mode) {
    // not really sure what wide orientation even means
    // and I tried to take inspiration from musl which doesn't seem to even use it
    // since POSIX says that orientation won't change after deciding,
    // I'll just return that it's byte oriented
    // TODO: what?
    return -1;
}

wchar_t *wcpcpy(wchar_t *restrict ws1, const wchar_t *restrict ws2) {
    do {
        *ws1++ = *ws2;
    } while (*ws2++);
    return ws1 - 1;
}
wchar_t *wcpncpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n) {
    wchar_t * end = NULL;
    for (size_t i = 0; i < n; i++) {
        if (end) {
            *ws1++ = 0;
            continue;
        }
        *ws1 = *ws2++;
        if (*ws1 == 0)
            end = ws1;
        ws1++;
    }
    return end ? end : ws1;
}
wchar_t *wcscpy(wchar_t *restrict ws1, const wchar_t *restrict ws2) {
    wcpcpy(ws1, ws2);
    return ws1;
}
wchar_t *wcsncpy(wchar_t *__restrict ws1, const wchar_t *__restrict ws2, size_t n) {
    wcpncpy(ws1, ws2, n);
    return ws1;
}

size_t wcslen(const wchar_t *ws) {
    size_t ret = 0;
    while (*ws++) ret++;
    return ret;
}
size_t wcsnlen(const wchar_t *ws, size_t maxlen) {
    size_t ret = 0;
    while (*ws++ && ret < maxlen) ret++;
    return ret;
}
wchar_t *wcscat(wchar_t *restrict ws1, const wchar_t *restrict ws2) {
    wcpcpy(ws1 + wcslen(ws1), ws2);
    return ws1;
}
wchar_t *wcsncat(wchar_t *restrict ws1, const wchar_t *restrict ws2, size_t n) {
    wchar_t * _ws1 = ws1;
    ws1 += wcslen(ws1);
    while (n && *ws2) n--, *ws1++ = *ws2++;
    *ws1 = 0;
    return _ws1;
}

int wcscmp(const wchar_t *ws1, const wchar_t *ws2) {
    for (size_t i = 0; ws1[i] || ws2[i]; i++) {
        if (ws1[i] != ws2[i]) {
            if (ws1[i] < ws2[i]) return -1;
            return 1;
        }
    }
    return 0;
}
int wcsncmp(const wchar_t *ws1, const wchar_t *ws2, size_t n) {
    for (size_t i = 0; i < n && (ws1[i] || ws2[i]); i++) {
        if (ws1[i] != ws2[i]) {
            if (ws1[i] < ws2[i]) return -1;
            return 1;
        }
    }
    return 0;
}
// TODO: implement fully when implementing LC_COLLATE
int wcscoll(const wchar_t *ws1, const wchar_t *ws2) {
    return wcscmp(ws1, ws2);
}

#include <wctype.h>
int wcscasecmp(const wchar_t *ws1, const wchar_t *ws2) {
    for (size_t i = 0; ws1[i] || ws2[i]; i++) {
        if (towlower(ws1[i]) != towlower(ws2[i])) {
            if (towlower(ws1[i]) < towlower(ws2[i])) return -1;
            return 1;
        }
    }
    return 0;
}
int wcsncasecmp(const wchar_t *ws1, const wchar_t *ws2, size_t n) {
    for (size_t i = 0; i < n && (ws1[i] || ws2[i]); i++) {
        if (towlower(ws1[i]) != towlower(ws2[i])) {
            if (towlower(ws1[i]) < towlower(ws2[i])) return -1;
            return 1;
        }
    }
    return 0;
}

wchar_t *wcschr(const wchar_t *ws, wchar_t wc) {
    do {
        if (*ws == wc)
            return (wchar_t*)ws;
    } while (*ws++);
    return NULL;
}
wchar_t *wcsrchr(const wchar_t *ws, wchar_t wc) {
    const wchar_t *_ws = ws + wcslen(ws);
    if (wc == 0)
        return (wchar_t*)_ws;
    while (_ws-- > ws)
        if (*_ws == wc)
            return (wchar_t*)_ws;
    return NULL;
}

size_t wcsspn(const wchar_t *ws1, const wchar_t *ws2) {
    size_t c = 0;
    while (*ws1) {
        for (size_t i = 0; ws2[i] != 0; i++)
            if (*ws1 == ws2[i])
                goto next;
        return c;
        next:
        c++;
        ws1++;
    }
    return c;
}

size_t wcscspn(const wchar_t *ws1, const wchar_t *ws2) {
    size_t c = 0;
    while (*ws1) {
        for (size_t i = 0; ws2[i] != 0; i++)
            if (*ws1 == ws2[i])
                return c;
        c++;
        ws1++;
    }
    return c;
}

wchar_t *wcsdup(const wchar_t *string) {
    size_t len = wcslen(string) + 1;
    wchar_t * new = malloc(len * sizeof(wchar_t));
    if (new == NULL)
        return NULL;

    wcscpy(new, string);
    return new;
}

wchar_t *wcspbrk(const wchar_t *ws1, const wchar_t *ws2) {
    do {
        for (size_t i = 0; ws2[i]; i++)
            if (*ws1 == ws2[i])
                return (wchar_t*)ws1;
    } while (*ws1++);
    return NULL;
}
wchar_t *wcsstr(const wchar_t *restrict ws1, const wchar_t *restrict ws2) {
    if (!*ws2) return (wchar_t*)ws1;
    if (!*ws1) return NULL;

    for (const wchar_t * _hs = ws1; *_hs != 0; _hs++) {
        for (const wchar_t *_ne = ws2, *_hs2 = _hs; *_ne == *_hs2 || !*_ne || !*_hs; _ne++, _hs2++) {
            if (!*_ne) return (wchar_t*)_hs;
            if (!*_hs2) return NULL;
        }
    }
    return NULL;
}

wchar_t *wmemchr(const wchar_t *ws, wchar_t wc, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (ws[i] == wc)
            return (wchar_t*)ws + i;
    }
    return NULL;
}

int wmemcmp(const wchar_t *ws1, const wchar_t *ws2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (ws1[i] < ws2[i])
            return -1;
        if (ws1[i] > ws2[i])
            return 1;
    }
    return 0;
}

#include <string.h>
wchar_t *wmemcpy(wchar_t *restrict ws1, const wchar_t *restrict ws2, size_t n) {
    memcpy(ws1, ws2, n * sizeof(wchar_t));
    return ws1;
}

wchar_t *wmemmove(wchar_t *ws1, const wchar_t *ws2, size_t n) {
    memmove(ws1, ws2, n * sizeof(wchar_t));
    return ws1;
}

wchar_t *wmemset(wchar_t *ws, wchar_t wc, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ws[i] = wc;
    }
    return ws;
}