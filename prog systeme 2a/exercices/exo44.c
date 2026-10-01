#include <signal.h>

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]){
    pid_t pid= getpid();
    printf("pid: %d\n",pid);
    while(1){}

}