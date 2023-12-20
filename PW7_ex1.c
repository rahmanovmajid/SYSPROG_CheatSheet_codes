#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
   int why;
   int pid= fork();

   if(pid == -1) exit(21);
   if(pid == 0){
      printf("child : %d, %d\n", getpid(), getppid());
      exit(getpid() % 10);
   }
   else {
      printf("parent: %d, %d\n", getpid(), getppid());
      wait(&why);
      if(WIFEXITED(why)){
         printf("exitcode, %d\n", WEXITSTATUS(why));
      }
      if(WIFSIGNALED(why)){
         printf("stopped by signal %d\n", WTERMSIG(why));
      }
   }
}
