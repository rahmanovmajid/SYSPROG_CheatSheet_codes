#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error 1\n");
        exit(1);
    }

    int fifo = mkfifo("foo", 0666); 

    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error 3\n");
        exit(3);
    } else if (pid == 0) {
        int fd = open("foo", O_WRONLY);
        dup2(fd, 1);
        close(fd);
        execlp("ps", "ps", "eaux", (char*)0);
        fprintf(stderr, "Error 4\n");
        exit(4);
    }
    int fd = open("foo", O_RDONLY);
    dup2(fd, 0);
    close(fd);

    int out = open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup2(out, 1);
    close(out);

    char *inp = (char*) malloc((strlen(argv[1]) + 3) * sizeof(char));
    inp[0] = '^';
    strcpy(inp + 1, argv[1]);
    inp[strlen(argv[1]) + 1] = ' ';
    execlp("grep", "grep", inp, (char*)0);

    return 5;
}
