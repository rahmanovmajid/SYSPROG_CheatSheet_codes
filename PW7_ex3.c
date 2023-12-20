#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include"color.h"


void lire_fichier(int desc,int desc2){
    char c;

    while ( read(desc,&c,sizeof(char)) > 0 ){
        write(desc2,&c,sizeof(char));
        printf("I am the process %d and I've read the letter:  %c\n",getpid(),c);
        sleep(1);
    }
}

int main(int argc,char *argv[]){
    pid_t pid;
    int desc,desc2;


    if ( argc < 2 ){
        printf("usage: %s filename\n",argv[0]);
        exit(1);
    }

    if ( (desc = open(argv[1], O_RDONLY)) < 0 ){
        perror("open error");
        exit(2);
    }


    pid = fork();
    switch (pid){
        case -1:
            perror("Error.");
            break;
        case 0:
            printf(FG_BLUE "Child Process : %d (and my Parent is : %d)\n" NOCOLOR,getpid(),getppid());
            lire_fichier(desc,desc2);
            break;
        default:
            printf(FG_GREEN "Parent Process : %d\n" NOCOLOR, getpid());
            lire_fichier(desc,desc2);
            break;
    }

    printf("Ended: %d\n",getpid());
    return 0;
}