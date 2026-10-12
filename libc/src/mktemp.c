#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_TRIES 100

#define TMPFILE_TEMPLATE "/tmp/XXXXXX" // if changing, change L_tmpnam

static void get_rand_string(char * start) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    size_t num = ts.tv_sec + ts.tv_nsec / 100 + pthread_self()->__tid * 30059;
    for (int i = 0; i < 6; i++, num = num >> 5 | num << 3) {
        start[i] = 'A' + num % 26 + (num & 0x80000 ? 0x20 : 0);
    }
}

char *tmpnam(char *s) {
    static char _s[L_tmpnam + 1];
    if (!s) s = _s;
    strcpy(s, TMPFILE_TEMPLATE);
    get_rand_string(s + sizeof(TMPFILE_TEMPLATE) - 1 - 6);
    return s;
}

char *mktemp(char *s) {
    if (s == NULL) {
        ___set_errno(EFAULT);
        return NULL;
    }

    struct stat st;
    size_t len = strlen(s);

    if (len < 6 || strcmp(s + len - 6, "XXXXXX")) {
        ___set_errno(EINVAL);
        s[0] = '\0';
        return s;
    }

    for (int i = 0; i < MAX_TRIES; i++) {
        get_rand_string(s + len - 6);
        if (stat(s, &st) == -1)
            if (___get_errno() == ENOENT)
                return s;
    }
    ___set_errno(EEXIST);
    return NULL;
}

char *mkdtemp(char *template) {
    if (template == NULL) {
        ___set_errno(EFAULT);
        return NULL;
    }
    size_t len = strlen(template);
    if (len < 6 || strcmp(template + len - 6, "XXXXXX")) {
        ___set_errno(EINVAL);
        return NULL;
    }

    struct stat st;

    for (int i = 0; i < MAX_TRIES; i++) {
        get_rand_string(template + len - 6);
        if (stat(template, &st) != -1 && ___get_errno() != ENOENT)
            continue;

        if (mkdir(template, S_IRWXU) < 0)
            continue;
        return template;
    }
    return NULL;
}
int mkostemp(char *template, int flag) {
    if (template == NULL) {
        ___set_errno(EFAULT);
        return -1;
    }
    size_t len = strlen(template);
    if (len < 6 || strcmp(template + len - 6, "XXXXXX")) {
        ___set_errno(EINVAL);
        return -1;
    }

    for (int i = 0; i < MAX_TRIES; i++) {
        get_rand_string(template + len - 6);
        int fd = open(template, O_CREAT | O_EXCL | O_RDWR | flag, S_IRUSR | S_IWUSR);
        if (fd < 0)
            continue;
        return fd;
    }
    return -1;
}
int mkstemp(char *template) {
    return mkostemp(template, 0);
}

FILE *tmpfile() {
    char path[sizeof(TMPFILE_TEMPLATE)];
    strcpy(path, TMPFILE_TEMPLATE);

    int fd;
    if ((fd = mkstemp(path)) < 0)
        return NULL;

    unlink(path);
    FILE * f = fdopen(fd, "w+");
    if (!f) close(fd);
    return f;
}

char *tempnam(const char *dir, const char *pfx) {
    if (dir == NULL)
        dir = P_tmpdir;
    if (pfx == NULL)
        pfx = "tmp";

    size_t len = strlen(dir) + 1 + strlen(pfx) + 6 + 1;
    if (len > PATH_MAX) {
        ___set_errno(ENAMETOOLONG);
        return NULL;
    }

    char * path = malloc(len);
    if (!path)
        return NULL; // errno set by malloc
    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, pfx);
    strcat(path, "XXXXXX");

    struct stat st;
    for (int i = 0; i < MAX_TRIES; i++) {
        get_rand_string(path + len - 1 - 6);
        if (stat(path, &st) != -1 && ___get_errno() != ENOENT)
            continue;
        return path;
    }
    free(path);
    return NULL;
}