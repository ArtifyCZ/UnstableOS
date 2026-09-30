#include <wchar.h>
#include <wctype.h>
#include <ctype.h>
#include "luts.h"
// hopefully correct, I have no clue


// tables are generated from https://www.unicode.org/Public/14.0.0/ucd/UnicodeData.txt
// some debatable ranged switches are from here https://www.open-std.org/JTC1/SC35/WG5/docs/30112d10.pdf

// is_int means casting to unsigned int instead of unsigned short
// ranges and similar are to be handled by the caller
// less-than-equal binary search
// I am fully aware how dogshit this is, no clue when I became such a horrible programmer
static const void * binary_search(const void * list, size_t elsize, size_t n, char is_int, wint_t el) {
    if (!is_int && el > 0xFFFF)
        return NULL;
    if (n == 0 || elsize == 0)
        return NULL;

    size_t start = 0;
    size_t end = n - 1;
    while (start < end && start < n && end < n && (end - start) / 2 > 0) {
        size_t test = start + (end - start) / 2;
        unsigned int test_val = 0;
        if (is_int)
            test_val = *(unsigned int*)(list + elsize * test);
        else
            test_val = *(unsigned short*)(list + elsize * test);
        if (test_val == el)
            return list + test * elsize;
        if (test_val > el)
            end = test - 1;
        else
            start = test;
    }
    // inaccuracy when (end-start) / 2 == 0
    if ((end-start) / 2 == 0) {
        unsigned int test_val = 0;
        if (is_int)
            test_val = *(unsigned int*)(list + elsize * end);
        else
            test_val = *(unsigned short*)(list + elsize * end);
        if (test_val <= el)
            start = end;
    }


    if (start > end)
        return NULL;
    if (end > n) // underflow
        return NULL;
    if (start > n - 1)
        return NULL;
    return list + start * elsize;
}

int iswdigit(wint_t wc) {
    return isdigit((int)wc);
}

int iswxdigit(wint_t wc) {
    return isxdigit((int)wc);
}

#define iswmacro(low, high) {                       \
    if (wc == WEOF) return 0;                       \
    unsigned int res[2];                            \
    if (wc > 0xFFFF) {                              \
        const unsigned int * _res = binary_search(  \
            (high),                                 \
            sizeof((high)[0]),                      \
            sizeof((high)) / sizeof((high)[0]),     \
            1, wc);                                 \
        if (_res == NULL)                           \
            return 0;                               \
        res[0] = _res[0];                           \
        res[1] = _res[1];                           \
    } else {                                        \
        const unsigned short * _res = binary_search(\
            (low),                                  \
            sizeof((low)[0]),                       \
            sizeof((low)) / sizeof((low)[0]),       \
            0, wc);                                 \
        if (_res == NULL)                           \
            return 0;                               \
        res[0] = _res[0];                           \
        res[1] = _res[1];                           \
    }                                               \
    if (res[0] > wc)                                \
        return 0;                                   \
    if (res[1] < wc)                                \
        return 0;                                   \
    return 1;                                       \
}
int iswupper(wint_t wc) {
    iswmacro(iswupper_ranges, iswupper_ranges_high)
}
int iswlower(wint_t wc) {
    iswmacro(iswlower_ranges, iswlower_ranges_high)
}
int iswpunct(wint_t wc) {
    iswmacro(iswpunct_ranges, iswpunct_ranges_high)
}
static int is_modif(wint_t wc) {
    iswmacro(modifier_letters, modifier_letters_high)
}
static int is_other(wint_t wc) {
    iswmacro(other_letters, other_letters_high)
}
static int is_titlecase(wint_t wc) {
    for (int i = 0; i < sizeof(titlecase_letters)/sizeof(titlecase_letters[0]); i++) {
        if (titlecase_letters[i] == wc)
            return 1;
    }
    return 0;
}

int iswalpha(wint_t wc) {
    return isalpha((int)wc) || iswupper(wc) || iswlower(wc) || is_modif(wc) || is_other(wc) || is_titlecase(wc);
}
int iswalnum(wint_t wc) {
    return isalnum((int)wc) || iswdigit(wc) || iswalpha(wc);
}
int iswspace(wint_t wc) {
    switch (wc) {
        case 9 ... 0xD:
        case 0x20:
        case 0x1680:
        case 0x180E:
        case 0x2000 ... 0x2006:
        case 0x2008 ... 0x200A:
        case 0x2028:
        case 0x2029:
        case 0x205F:
        case 0x3000:
            return 1;
        default:
            return 0;
    }
}
int iswcntrl(wint_t wc) {
    switch (wc) {
        case 0 ... 0x1F:
        case 0x7F ... 0x9F:
        case 0x2028:
        case 0x2029:
            return 1;
        default:
            return 0;
    }
}
int iswblank(wint_t wc) {
    switch (wc) {
        case 9 ... 0x20:
        case 0x1680:
        case 0x180E:
        case 0x2000 ... 0x2006:
        case 0x2008 ... 0x200A:
        case 0x205F:
        case 0x3000:
            return 1;
        default:
            return 0;
    }
}


static int is_the_rest(wint_t wc) {
    iswmacro(the_rest, the_rest_high)
}
int iswprint(wint_t wc) {
    if (wc == WEOF) return 0;
    return isprint((int)wc) || is_the_rest(wc) || iswspace(wc) || iswblank(wc) || iswpunct(wc) || iswalnum(wc);
}

int iswgraph(wint_t wc) {
    if (wc == WEOF) return 0;
    return !iswspace(wc) && iswprint(wc);
}

static int is_nontrivial(wint_t wc) {
    iswmacro(towupper_exclusions, towupper_exclusions_high)
}

wint_t towlower(wint_t wc) {
    if (wc == WEOF) return WEOF;
    if (!iswupper(wc))
        return wc;
    if (is_nontrivial(wc))
        return wc;
    if (wc > 0xFFFF) {
        const unsigned int * ex = binary_search(
            towupper_delta_list_high,
            sizeof(towupper_delta_list_high[0]),
            sizeof(towupper_delta_list_high)/sizeof(towupper_delta_list_high[0]),
            1, wc);
        if (!ex)
            return wc;
        if (ex[0] > wc || ex[1] < wc)
            return wc;
        return wc - ex[2];
    }
    const unsigned short * ex = binary_search(
        towupper_delta_list_ex,
        sizeof(towupper_delta_list_ex[0]),
        sizeof(towupper_delta_list_ex)/sizeof(towupper_delta_list_ex[0]),
        0, wc);
    if (ex && ex[0] == wc) {
        if (ex[2])
            return wc - ex[1];
        return wc + ex[1];
    }
    ex = binary_search(
        towupper_delta_list,
        sizeof(towupper_delta_list[0]),
        sizeof(towupper_delta_list)/sizeof(towupper_delta_list[0]),
        0, wc);
    if (!ex)
        return wc;
    if (ex[0] > wc || ex[1] < wc)
        return wc;
    if (ex[3])
        return wc - ex[2];
    return wc + ex[2];
}

wint_t towupper(wint_t wc) {
    if (wc == WEOF) return WEOF;
    // for my dearest Adrian, and not so dear Miezekatze; fuck special casing rules, grr
    if (wc == L'ß')
        return L'ẞ';
    if (!iswlower(wc))
        return wc;
    if (is_nontrivial(wc))
        return wc;
    if (wc > 0xFFFF) {
        const unsigned int * ex = binary_search(
            towupper_delta_list_high,
            sizeof(towupper_delta_list_high[0]),
            sizeof(towupper_delta_list_high)/sizeof(towupper_delta_list_high[0]),
            1, wc);
        if (!ex)
            return wc;
        if (ex[0] > wc || ex[1] < wc)
            return wc;
        return wc + ex[2];
    }
    const unsigned short * ex = binary_search(
        towupper_delta_list_ex,
        sizeof(towupper_delta_list_ex[0]),
        sizeof(towupper_delta_list_ex)/sizeof(towupper_delta_list_ex[0]),
        0, wc);
    if (ex && ex[0] == wc) {
        if (ex[2])
            return wc + ex[1];
        return wc - ex[1];
    }
    ex = binary_search(
        towupper_delta_list,
        sizeof(towupper_delta_list[0]),
        sizeof(towupper_delta_list)/sizeof(towupper_delta_list[0]),
        0, wc);
    if (!ex)
        return wc;
    if (ex[0] > wc || ex[1] < wc)
        return wc;
    if (ex[3])
        return wc + ex[2];
    return wc - ex[2];
}

#include <string.h>

#define WC_INVALID 0

#define WCTYPES \
    X(alnum, 1)   \
    X(alpha, 2)   \
    X(blank, 3)   \
    X(cntrl, 4)   \
    X(digit, 5)   \
    X(graph, 6)   \
    X(lower, 7)   \
    X(print, 8)   \
    X(punct, 9)   \
    X(space, 10)  \
    X(upper, 11)  \
    X(xdigit, 12)

#define X(m, v) [v] = isw ## m,
static int (*const iswfuncs[])(wint_t wc) = {
    WCTYPES
};
#undef X
#define X(m, v) [v] = #m,
static const char *const classes[] = {
    WCTYPES
};
#undef X

wctype_t wctype(const char *property) {
    for (int i = 0; i < sizeof(classes)/sizeof(char*); i++)
        if (classes[i] && strcmp(property, classes[i]) == 0)
            return i;
    return WC_INVALID;
}

int iswctype(wint_t wc, wctype_t charclass) {
    if (wc == WEOF) return 0;
    if (charclass == WC_INVALID || charclass >= sizeof(iswfuncs) / sizeof(iswfuncs[0]))
        return 0;
    return iswfuncs[charclass](wc);
}

#define TRANS_UPPER 1
#define TRANS_LOWER 2

wctrans_t wctrans(const char *charclass) {
    if (strcmp(charclass, "upper") == 0)
        return TRANS_UPPER;
    if (strcmp(charclass, "lower") == 0)
        return TRANS_LOWER;
    return 0;
}
wint_t towctrans(wint_t wc, wctrans_t desc) {
    if (wc == WEOF)
        return WEOF;
    switch (desc) {
        case TRANS_UPPER:
            return towupper(wc);
        case TRANS_LOWER:
            return towlower(wc);
        default:
            return wc;
    }
}