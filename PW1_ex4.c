#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 100;

char *reformat_string(char *str) {
    size_t len = strlen(str);
    char *new_str = (char*) calloc(len, sizeof(char));
    int count = 0;
    for (int i = 0; i < len; i++) {
        if ((str[i] > 31 && str[i] < 127) && str[i] != 92) {
            new_str[count++] = str[i];
        } else if (str[i] == 92) {
            i++;
            switch(str[i]){
              case 't':
                new_str[count++] = '\t';
                break;
              case 'n':
                new_str[count++] = '\n';
                break;
              case 'r':
                new_str[count++] = '\r';
                break;
              case 'b':
                new_str[count++] = '\b';
                break;
              case 92:
                new_str[count++] = 92;
                break;
            }

        }
    }
    new_str[count] = '\0';
    return new_str;
}

int main(int argc, char *argv[]) {
    char str[MAX];
    printf("String: ");
    fgets(str, MAX, stdin);
    char *new_str = reformat_string(str);

    printf("String: %s\n", new_str);

    free(new_str);
    return 0;
}

