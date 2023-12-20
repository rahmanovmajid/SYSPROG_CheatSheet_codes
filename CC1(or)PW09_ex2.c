// GULIYEV Fahmin - marked PW - thursday, Dec. 5th.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    char *passedName; 
    if (argc == 2) {
        passedName = (char*) malloc((strlen(argv[1]) + 1) * sizeof(char));
        strcpy(passedName, argv[1]);
    }
    else {
        passedName = getenv("root");
    }

    int pipe2[2];   //we'll need three pipes for parent and 2 children
    if ( pipe(pipe2) == -1 ) {
        fprintf(stderr, "Error 1\n");
        exit(1);
    }
    int pid2 = fork();
    if (pid2 == -1) {
        fprintf(stderr, "Error 2\n");
        exit(2);
    } 
    else if (pid2 == 0) { // child 2
        int pipe1[2];
        if (pipe(pipe1) == -1) {
            fprintf(stderr, "Error 3\n");
            exit(3);
        }
        // when 1 is on
        int pid1 = fork();
        if (pid1 == -1) {
            fprintf(stderr, "Error 3\n");
            exit(3);
        } else if (pid1 == 0) { // child 1
            close(pipe1[0]);
            dup2(pipe1[1], 1);
            close(pipe1[1]);
            execlp("ps", "ps", "eaux", NULL);
            fprintf(stderr, "Error 4\n");
            exit(4);
        }
        // when 2 is on
        close(pipe1[1]);
        dup2(pipe1[0], 0);
        close(pipe1[0]);

        close(pipe2[0]);
        dup2(pipe2[1], 1);
        close(pipe2[1]);
        
        execlp("grep", "grep", passedName, NULL);
        fprintf(stderr, "Error 5\n");
        exit(5);
    }
    
    // when 3 is on
    close(pipe2[1]);
    dup2(pipe2[0], 0);
    close(pipe2[0]);
    execlp("wc", "wc", "-l", NULL);
    fprintf(stderr, "Error 6\n");
    exit(6);

    return 0;
}