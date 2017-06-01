#include "clearCache.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // for close

int clearCache(){
    int fd;
    char* data = "3";
    sync();
    fd = open("/proc/sys/vm/drop_caches", O_WRONLY);
    write(fd, data, sizeof(char));
    close(fd);
    return 0;
}