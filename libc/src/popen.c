#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

extern FILE * __files;

FILE *popen(const char *command, const char *mode) {
    int pipes[2];
    int dir;
    if (mode[0] == 'r')
        dir = 0;
    else if (mode[0] == 'w')
        dir = 1;
    else {
        ___set_errno(EINVAL);
        return NULL;
    }
    if (pipe2(pipes, O_CLOEXEC)) return NULL;
    FILE * ret = fdopen(pipes[dir], mode);
    if (!ret) {
        close(pipes[0]);
        close(pipes[1]);
        return NULL;
    }
    pid_t child;
    switch ((child = fork())) {
        case -1:
            fclose(ret);
            close(pipes[!dir]);
            return NULL;
        case 0:
            // POSIX says every popen file descriptor regardless of O_CLOEXEC gets closed
            while (__files)
                if (__files->popen_pid)
                    close(__files->fd);
            dup2(pipes[!dir], !dir);
            execlp("sh", "sh", "-c", "--", command, NULL);
            exit(127);
        default:
    }
    // TODO: racy with another perfectly timed popen
    ret->popen_pid = child;
    if (!strchr(mode, 'e'))
        fcntl(pipes[dir], F_SETFD, 0);
    close(pipes[!dir]);
    return ret;
}
int pclose(FILE *stream) {
    // so we can close sooner
    pid_t p = stream->popen_pid;
    fclose(stream);
    int wstatus;
    int ret;
    while ((ret = waitpid(p, &wstatus, 0)) < 0 && ___get_errno() == EINTR) {}
    if (ret < 0)
        return -1;
    return wstatus;
}