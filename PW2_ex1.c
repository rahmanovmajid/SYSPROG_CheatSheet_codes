#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
   if(argc != 3){
      printf("Usage: %s <from> <to>. Where <from> is a file to copy from and <to> file to copy to", argv[0]);
      return -1;
   }

   const char *from= argv[1], *to= argv[2];

   FILE *readFile= fopen(from, "r");
   FILE *writeFile= fopen(to, "w");


   if(!readFile || !writeFile){
      printf("Couldn't open the file\n");
      return -2;
   }

   char c;

   while((c=getc(readFile)) != EOF){
      putc(c, writeFile);
   }

   fclose(readFile);
   fclose(writeFile);

   return 0;
}
