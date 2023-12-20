#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error 1\n");
        exit(1);
    }

    int pipes[2];

    if (pipe(pipes) == -1) {
        fprintf(stderr, "Error 2\n");
        exit(2);
    }

    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error 3\n");
        exit(3);
    } else if (pid == 0) {
        close(pipes[0]);
        dup2(pipes[1], 1);
        close(pipes[1]);
        execlp("ps", "ps", "eaux", (char*)0);
        fprintf(stderr, "Error 4\n");
        exit(4);
    }
    close(pipes[1]);
    dup2(pipes[0], 0);
    close(pipes[0]);
    int fd = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    dup2(fd, 1);
    close(fd);
    char *in = (char*) malloc((strlen(argv[1]) + 3) * sizeof(char));
    in[0] = '^';
    strcpy(in + 1, argv[1]);
    in[strlen(argv[1]) + 1] = ' ';
    execlp("grep", "grep", in, (char*)0);

    return 5;
}
