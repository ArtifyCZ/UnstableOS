#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

int system(const char *command) {
    pthread_testcancel();

    struct sigaction sigint, sigquit;
    sigset_t old, new;

    int wstatus = 0;
    pid_t child;

    // here to prevent a race between fork and execlp
    sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_IGN}, &sigint);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, &sigquit);
    sigemptyset(&new);
    sigaddset(&new, SIGCHLD);
    sigprocmask(SIG_BLOCK, &new, &old);
    switch ((child = fork())) {
        case -1:
            return -1;
        case 0:
            sigprocmask(SIG_SETMASK, &old, NULL);
            sigaction(SIGQUIT, &sigquit, NULL);
            sigaction(SIGINT, &sigint, NULL);
            execlp("sh", "sh", "-c", "--", command, NULL);
            exit(127);
        default:
            while (waitpid(child, &wstatus, 0) < 0 && ___get_errno() == EINTR) {}
    }

    sigprocmask(SIG_SETMASK, &old, NULL);
    sigaction(SIGQUIT, &sigquit, NULL);
    sigaction(SIGINT, &sigint, NULL);

    return wstatus;
}