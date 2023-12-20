#include <stdio.h>

char getchar1() {
    return (char) getc(stdin);
}

int main(int argc, char *argv[]) {
    printf("%c\n", getchar1());

    return 0;
}
