#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct myFile{
    int file;
    char buffer[200];
}myFile;

int my_open(char name[]){
    int file= open(name,O_RDWR);
    if(file<0) return 1;
    else file;
}

int my_getc (myFile my){
   return read(my.file,my.buffer,200);
}

void my_putc(myFile my){
    write(1, my.buffer, strlen(my.buffer));
    printf("\n");
}

void my_close(myFile my){
    close(my.file);
}

int main(int argc, char const *argv[]){
    myFile f;
    f.file = my_open("foo.txt");
    int count = my_getc(f);
    my_putc(f);
    my_close(f);
    return 0;
}
