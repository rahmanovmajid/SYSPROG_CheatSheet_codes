#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct month{
   char name[9 + 1];
   int days;
} month;

int main(int argc, char const *argv[]) {
   month months[12]= {"January\n", 31, "February\n", 28, "March\n", 31, "April\n", 30, "May\n", 31, "June\n", 30, "July\n", 31, "August\n", 31, "September\n", 30, "October\n", 31, "November\n", 30, "December\n", 31};
   int c = 0;

   char input[10];
   fgets(input, 10, stdin);


   for(int i=0; i< 12; i++){
      if(strcmp(input, months[i].name) == 0)
         printf("Month number is: %d Number of days is %d\n", i+1, months[i].days);
         c++;
   }

   if ( c == 0 )  printf("Invalid month.\n");

   return 0;
}

