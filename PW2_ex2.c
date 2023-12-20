#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int num_of_el(char *str);
int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");

    int c = 0;
    int num_of_lines = 0;
    if ((c = getopt(argc, argv, "n:")) == 'n') {
        num_of_lines = atoi(optarg);
    }

    fseek(f, 0, SEEK_END);
    int num_of_chars = ftell(f);
    fseek(f, 0, SEEK_SET);
    int count = 1;
    while (count < num_of_chars) {
        fseek(f, -count, SEEK_END);
        char str[count];
        fread(str, 1, count, f);
        count++;
        if (num_of_el(str) >= num_of_lines || count >=num_of_chars) {
            if (count >=num_of_chars)
                printf("%s\n", str);
            else
                printf("%s\n", str + 1);
            break;
        }
    }

    fclose(f);
    return 0;
}

int num_of_el(char *str) {
    int count = 0;
    for(size_t i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') count++;
    }
    return count;
}
