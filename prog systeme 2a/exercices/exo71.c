//amelioration de exo7 avec pread et pwrite

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd = -1;
    int value = 42;
    ssize_t ret = 0;
    ssize_t ret_value = 0;
    int value2=0;

    
    fd = open("entier.txt",O_RDWR | O_CREAT, S_IRWXU);
    assert(fd > 0);

    ret = pwrite(fd, &value, sizeof(value), 0);
    assert(ret > 0);

    ret_value = pread(fd, &value2, sizeof(int), 0);
    fprintf(stdout, "valeur lue = %i\n", value2);

    exit(EXIT_SUCCESS);
}