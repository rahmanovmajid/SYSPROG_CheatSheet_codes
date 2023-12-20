#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error 1\n");
        exit(1);
    }

    int pid1 = fork();
    if (pid1 == -1) {
        fprintf(stderr, "Error 3\n");
        exit(3);
    } else if (pid1 == 0) {
        int pipes[2];

        if (pipe(pipes) == -1) {
            fprintf(stderr, "Error 2\n");
            exit(2);
        }

        int pid2 = fork();
        if (pid2 == -1) {
            fprintf(stderr, "Error 3\n");
            exit(3);
        } else if (pid2 == 0) {
            close(pipes[0]);
            dup2(pipes[1], 1);
            close(pipes[1]);
            execlp("ps", "ps", "eaux", (char*)0);
            fprintf(stderr, "Error 4\n");
            exit(4);
        } else {
            close(pipes[1]);
            dup2(pipes[0], 0);
            close(pipes[0]);

            int out = open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0666);
            dup2(out, 1);
            close(out);

            char *in = (char*) malloc((strlen(argv[1]) + 2) * sizeof(char));
            in[0] = '^';
            strcpy(in + 1, argv[1]);
            
            execlp("grep", "grep", in, (char*)0);
            fprintf(stderr, "Error 4\n");
            exit(4);
        }
    }

    int why;
    wait(&why);
    if (WEXITSTATUS(why) == 0) {
        char *out = (char*) malloc((strlen(argv[1]) + 16) * sizeof(char));
        strcpy(out, argv[1]);
        strcpy(out + strlen(argv[1]), " is connected\n");
        write(1, out, strlen(out));
    }


    return 0;
}
