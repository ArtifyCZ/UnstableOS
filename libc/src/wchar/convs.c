#include <wchar.h>
#include <errno.h>

size_t wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict ps) {
    if (!s)
        return 1;

    // the maximum value representable in a UTF-8 codepoint
    // defined up to U+10FFFF (SPUA-B)
    // actual maximum is U+1FFFFF
    if (wc < 0 || wc > 0x10FFFF) {
        ___set_errno(EILSEQ);
        return WEOF;
    }

    wint_t c = wc;
    int b = 0;
    // 1 bit more than representable in the continuation to not produce extra bytes
    while (c & ~0x7F) {
        b++;
        c >>= 6;
    }
    if (b == 0) {
        *s = c;
        return 1;
    }
    if (__builtin_clz(c) - 24 < b + 2)
        b++;
    c = wc;
    int i = b;
    while (c & ~0x7F) {
        s[i] = (c & 0x3F) | 0x80;
        i--;
        c >>= 6;
    }
    if (__builtin_clz(c) - 24 < b + 1) {
        s[i] = (c & 0x3F) | 0x80;
        i--;
        c >>= 6;
    }
    int final = 0b11111111 & ~((1 << (7 - b)) - 1);
    final |= (int)c;
    s[0] = final;
    return b;
}
int wctomb(char *s, wchar_t wchar) {
    size_t ret = wcrtomb(s, wchar, NULL);
    return ret == WEOF ? -1 : ret;
}



size_t mbrtowc(wchar_t *restrict pwc, const char *restrict s, size_t n, mbstate_t *restrict ps) {
    static mbstate_t internal = 0;
    wchar_t __pwc;
    const unsigned char * _s = (void*)s;

    if (!ps)
        ps = &internal;
    if (!s) {
        if (*ps)
            goto ilseq;
        return 0;
    }
    if (!pwc)
        pwc = &__pwc;

    int i = 0;
    if (*ps == 0) {
        if (*_s < 128) {
            *pwc = (wchar_t)*_s;
            return 1;
        }
        unsigned int w = __builtin_clz((unsigned char)~*_s) - 24;
        if (w > 4 || w == 1)
            goto ilseq;
        w--;
        *ps = *_s & ((1 << (6 - w)) - 1);
        *ps |= w << 30;
        i++;
    }

    unsigned int remain = *ps >> 30;

    for (; i < n; i++) {
        if (*ps & (3<<30) && (_s[i] & 0xC0) != 0x80)
            goto ilseq;
        *ps <<= 6;
        *ps |= _s[i] & 0x3F;
        remain--;
        if (remain == 0) {
            *pwc = *ps;
            *ps = 0;
            return n - i;
        }
    }
    *ps &= ~(3 << 30);
    *ps |= remain << 30;
    return -2;
    ilseq:
    ___set_errno(EILSEQ);
    *ps = 0;
    return -1;
}

size_t mbrlen(const char *restrict s, size_t n, mbstate_t *restrict ps) {
    mbstate_t internal;
    return mbrtowc(NULL, s, n, ps != NULL ? ps : &internal);
}