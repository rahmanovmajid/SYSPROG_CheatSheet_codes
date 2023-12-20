#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

   char input[100];
   fgets(input, 100, stdin);

   char data[100];
   strncpy(data, input, 100);

   puts(data);
   int length = strlen(data);

   printf("Input is: %s  It's length is: %d\n", data, length);

   return 0;
}

