#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char *getlogin() {
    return getenv("LOGNAME");
}
int getlogin_r(char *name, size_t namesize) {
    const char * logname = getenv("LOGNAME");
    if (!logname) return ENXIO; // by far the most fitting of the errors
    if (strlen(logname) >= namesize) return ERANGE;
    strcpy(name, logname);
    return 0;
}