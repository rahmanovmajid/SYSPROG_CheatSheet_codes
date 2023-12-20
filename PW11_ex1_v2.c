#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#define true 1

unsigned long long int COUNTER = 0;

void handler(int sig_code){
    char buff[100];
    int fd = open("./file.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
    time_t t;
    struct tm tm;
    switch (sig_code){
        case SIGINT:
            t = time(NULL);
            tm = *localtime(&t);
                
            sprintf(buff, "Date: %d.%d.%d\tCounter value: %llu\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, COUNTER);
            if(write(fd, &buff, strlen(buff)) == -1)
                fprintf(stderr, "Cannot write data to file!\n");
            close(fd);
            break;
        case SIGTERM:
            strcpy(buff, "end\n");
            if(write(fd, &buff, strlen(buff)) == -1)
                fprintf(stderr, "Cannot write data to file!\n");
            exit(0);
            break;
    }
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = handler;

    sigemptyset(&action.sa_mask);
    
    action.sa_flags = SA_RESTART;
    if(sigaction(SIGINT, &action, NULL) != 0){
        fprintf(stderr, "Error setting up the handler!\n");
        exit(1);
    }
    if(sigaction(SIGTERM, &action, NULL) != 0){
        fprintf(stderr, "Error setting up the handler!\n");
        exit(1);
    }

    while(true){ COUNTER++; }
}
