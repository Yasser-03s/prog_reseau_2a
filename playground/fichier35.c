#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    
    int fd= -1;
    fd= open("toto.txt", O_RDWR);
    assert(fd>0);
    printf("l'FD est: %d\n",fd);
    close(fd);


    exit(0);

}