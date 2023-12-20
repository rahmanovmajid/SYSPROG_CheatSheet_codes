#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
#include "color.h"


/shared_file.c/
int main(int argc, char * argv[]){

  int fd, status;
  pid_t cpid;
  char c;

  if ( argc < 2){
    fprintf(stderr, "ERROR: Require path\n");
    return 1;
  }

  //shared between all children and parent
  if( (fd = open(argv[1], O_RDONLY)) < 0){
    perror("open");
    return 1;
  }
cpid = fork();
    

    if( cpid == 0 ){
     // int status;
      while(read(fd, &c, 1) > 0){
        // wait(&status);
        // write(1,&c,1);
        printf(FG_BLUE "%c\n", c);
        // _exit(0); 
      }
    }else if ( cpid > 0){
      // wait(&status);
      while( read(fd, &c, 1) > 0)
        // write(1,&c,1);
        printf(FG_RED "%c\n", c); 
    }
  

  close(fd);

  return 0;
}