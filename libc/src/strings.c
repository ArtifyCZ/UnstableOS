#include <strings.h>
#include <string.h>

int bcmp(const void *s1, const void *s2, size_t n) {
    return memcmp(s1, s2, n);
}

void bcopy(const void *s1, void *s2, size_t n) {
    memmove(s2, s1, n);
}

void bzero(void *s, size_t n) {
    memset(s, 0, n);
}

char *index(const char *s, int c) {
    return strchr(s, c);
}

char *rindex(const char *s, int c) {
    return strrchr(s, c);
}

int ffs(int i) {
    return __builtin_ffs(i);
}
int ffsl(long i) {
    return __builtin_ffsl(i);
}
int ffsll(long long i) {
    return __builtin_ffsll(i);
}

// TODO: change to use current locale
#include <ctype.h>
int strcasecmp(const char *s1, const char *s2) {
    for (size_t i = 0; s1[i] || s2[i]; i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            if (tolower(s1[i]) < tolower(s2[i])) return -1;
            return 1;
        }
    }
    return 0;
}
int strncasecmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n && (s1[i] || s2[i]); i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            if (tolower(s1[i]) < tolower(s2[i])) return -1;
            return 1;
        }
    }
    return 0;
}