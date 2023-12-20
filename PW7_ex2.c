#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(){

    pid_t p;
    int n;
    int status;

    printf("Enter #processes for duplication: ");
    scanf("%d",&n);
    

    for ( int i = 0 ; i < n ; i++ ){
        p = fork();
        if ( p == -1 ){
            printf("Problem occured with fork().\n");
            exit(1);
        }
        else if ( p == 0 ){
            printf("I am the process: %d\n",getpid());
            exit(i);
        }
    }


    for ( int i = 0 ; i < n ; i++ ){
        p = wait(&status);
        printf("Process %d just terminated with code %d\n",p,WEXITSTATUS(status));
    }

    return 0;
}