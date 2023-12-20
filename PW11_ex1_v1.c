#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

int counter;

void handlerInt (int number)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    FILE *fp;
    if(number == SIGINT){
        printf("Interruption detected... saving...\n");
        fp=fopen("sav.txt", "a");
        fprintf(fp, "\nCounter: %d ;", counter);
        fprintf(fp, "Date: %s ", s);
        fclose(fp); 
        printf("saving completed, exiting...\n");
        exit(0);
    }
}

void handlerTerm (int number)
{
    FILE *fp;
    if(number == SIGTERM){
        printf("Interruption detected... ending the program...\n");
        fp=fopen("sav.txt", "a");
        fprintf(fp, "\nEND.");
        fclose(fp); 
        printf("saving completed, exiting...\n");
        exit(0);
    }
}

int main(void)
{
    printf("My pid is: %d\n", getpid());
    char cont='y';
    struct sigaction action;
    action.sa_handler = handlerInt;
    sigemptyset(&action.sa_mask);
    action.sa_flags=0;
    if(sigaction(SIGINT, &action, NULL) !=0){
        fprintf(stderr, "error setting up the handler\n");
        exit(1);
    }
    
    struct sigaction action2;
    action2.sa_handler = handlerTerm;
    sigemptyset(&action2.sa_mask);
    action2.sa_flags=0;
    if(sigaction(SIGTERM, &action2, NULL) !=0){
        fprintf(stderr, "error setting up the handler\n");
        exit(1);
    }

    while (1){
        counter++;
        printf("%d\n", counter);
        sleep(1);
    }
}
