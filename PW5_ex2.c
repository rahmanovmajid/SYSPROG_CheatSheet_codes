/*
 * C Program to List Files in Directory
 */
#include <dirent.h>
#include <stdio.h>


int main(int argc, char **argv)
{
   if(argc != 2){
      printf("%s\n", "Usage: ./exDir [argument]");
      return -1;
   }

    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //printf("%ld \t %s\n", dir->d_ino, dir->d_name);
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}
