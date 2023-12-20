#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // execlp("ps", "ps", "eaux", NULL);
    if (argc != 2) {
        fprintf(stderr, "Error\nEnter file name as argument...\n");
        exit(1);
    }

    // if(S_ISDIR(argv[1]))  printf(" Its a directoy\n");
    // else exit(4);

    int tube[2];
    int v;
    int pid;
    int why;

    // v=pipe(tube);
    // if (v==-1) {exit(3);}

    

  pid = fork();
  if (pid == -1) {exit(20); }
  if (pid ==0)
    { // child
      int fd1;
      fd1=open("/dev/null", O_CREAT|O_WRONLY,0666);
      dup2(fd1, 1);
      close(fd1);
      execlp("/bin/ls", "ls", "-R",argv[1] ,NULL);      
      exit(5);
    }

  else
    { // parent
        printf("parent : launching the child...\n");
        wait(&why);
        if(WIFEXITED(why)) printf("parent : exit code is %d\n", WEXITSTATUS(why));
    }


    return 0;
}
