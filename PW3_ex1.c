#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd_r = open("foo", O_RDONLY);
    if (fd_r == -1) {
        perror("Cannot open the file foo");
        exit(1);
    }

    int fd_w = open("bar", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_w == -1) {
        perror("Cannot create the file bar");
        exit(1);
    }

    char buf[100];
    int readed = 0;
    do {
        readed = read(fd_r, buf, 100);
        write(fd_w, buf, readed);
    } while(readed > 0);

    close(fd_r);
    close(fd_w);

    return 0;
}
