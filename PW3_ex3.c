#include <stdio.h>

char buffer[100];

char getchar2() {
    static int buf_i = 0;
    return (char) (buffer[buf_i++] = getc(stdin));
}

int main(int argc, char *argv[]) {
    printf("%c\n", getchar2());

    return 0;
}
