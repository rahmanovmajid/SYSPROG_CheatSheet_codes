#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    
    if (argc != 2) {
        fprintf(stderr, "Error\nEnter file name as argument...\n");
        exit(1);
    }

    int tube[2];
    int v;
    int pid;

    v=pipe(tube);
    if (v==-1) {exit(3);}
    pid=fork();
    if (pid==-1) {exit(5);}
    if (pid==0)
    {
      //child "ls -l"
      close(tube[0]);
      dup2(tube[1], 1);
      close(tube[1]);
      execlp("ls", "ls", "-all", NULL);
    }
  else
    {
      //parent "wc -l"
      close(tube[1]);
      dup2(tube[0], 0);
      close(tube[0]);
      execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
