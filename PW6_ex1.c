#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void dividing(char* name, char** new){
    int j=0;
    for(int i=0;i<(int)strlen(name);i++){
        if(name[i]==':') {j++; continue;}
        new[j][i]=name[i];
    }
}



int main(int argc, char const *argv[])
{
    char* name = getenv("PATH");
    char** new;

    int count=0;
    for(int i=0;i<(int)strlen(name);i++){
        if (name[i]==':') count++;
    }
    count++;

    new = (char **)malloc(count * sizeof(char *));
    for (int i=0; i<count; i++) new[i] = (char *)malloc(((int)strlen(name)) * sizeof(int));

    dividing(name,new);

    for(int i=0;i<count;i++){
        for(int k=0;k<(int)strlen(name);k++){
            printf("%c",new[i][k]);
        }
        printf("\n");
    }

    printf("\n\n");

    printf("ls : %s\n", getenv("ls"));
    return 0;
}
