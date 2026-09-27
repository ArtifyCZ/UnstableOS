#include <wchar.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

// UTF-8
// TODO: exclude unassigned planes 4 - 13, and holes in plane 1 and 3 with EILSEQ

// basically a copy of mbrtowc(), but we can simplify parts of it here
wint_t fgetwc(FILE *stream) {
    int c = fgetc(stream);
    if (c == EOF)
        return WEOF;
    int remaining_to_read = __builtin_clz((unsigned char)~c) - 24;
    if (remaining_to_read == 0)
        return c;

    if (remaining_to_read > 4 || remaining_to_read == 1)
        goto ilseq;
    remaining_to_read--;

    wint_t code = (unsigned char)c & ((1 << (6 - remaining_to_read)) - 1);
    while (remaining_to_read--) {
        c = fgetc(stream);

        if (c == EOF)
            return WEOF;
        if ((c & 0xC0) != 0x80)
            goto ilseq;
        code <<= 6;
        code |= (unsigned char)c & 0x3F;
    }
    return code;

    ilseq:
    ___set_errno(EILSEQ);
    return WEOF;
}
wint_t getwc(FILE *stream) {
    return fgetwc(stream);
}

wint_t getwchar() {
    return fgetwc(stdin);
}

// basically a copy of wcrtomb(), but we can simplify parts of it here
wint_t ungetwc(wint_t wc, FILE *stream) {
    if (wc == WEOF)
        return WEOF;
    // the maximum value representable in a UTF-8 codepoint
    // defined up to U+10FFFF (SPUA-B)
    // actual maximum is U+1FFFFF
    if (wc > 0x10FFFF) {
        ___set_errno(EILSEQ);
        return WEOF;
    }

    wint_t c = wc;
    int b = 0;
    // 1 bit more than representable in the continuation to not produce extra bytes
    while (c & ~0x7F) {
        if (ungetc((int)(c & 0x3F) | 0x80, stream) == EOF)
            return WEOF;
        b++;
        c >>= 6;
    }
    if (b == 0) {
        if (ungetc((int)c, stream) == EOF)
            return WEOF;
        return wc;
    }
    b++;
    if (__builtin_clz(c) - 24 < b + 1) {
        if (ungetc((int)(c & 0x3F) | 0x80, stream) == EOF)
            return WEOF;
        c >>= 6;
    }
    int final = 0b11111111 & ~((1 << (8 - b)) - 1);
    final |= (int)c;
    if (ungetc(final, stream) == EOF)
        return WEOF;
    return wc;
}

wchar_t *fgetws(wchar_t *restrict ws, int n, FILE *restrict stream) {
    if (n <= 0)
        return ws;
    if (n == 1) {
        ws[n-1] = 0;
        return ws;
    }

    flockfile(stream);
    wint_t c = 0;
    int i = 0;
    for (; i < n-1; i++) {
        if (c == '\n') break;
        if ((c = fgetwc(stream)) == WEOF) {
            funlockfile(stream);
            return NULL;
        }
        ws[i] = (wchar_t)c;
    }
    funlockfile(stream);
    ws[i] = 0;
    return ws;
}

#include <stdlib.h>
wint_t fputwc(wchar_t wc, FILE *stream) {
    char buf[MB_CUR_MAX];
    size_t n = wcrtomb(buf, wc, NULL);
    if (n == WEOF)
        return WEOF;
    for (size_t i = 0; i < n; i++) {
        if (fputc((unsigned char)buf[i], stream) == EOF)
            return WEOF;
    }
    return wc;
}

wint_t putwc(wchar_t wc, FILE *stream) {
    return fputwc(wc, stream);
}

wint_t putwchar(wchar_t wc) {
    return fputwc(wc, stdout);
}

int fputws(const wchar_t *restrict ws, FILE *restrict stream) {
    while (*ws) {
        if (fputwc(*ws, stream) == WEOF)
            return -1;
        ws++;
    }
    return 0;
}