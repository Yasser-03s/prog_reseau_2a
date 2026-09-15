#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>


int main(int argc, char * argv[]){
    pid_t pid = -1;
    pid = fork();
    if (pid>0){
        printf("mon pid est: %d\n", getpid());
        exit(0);
    }
    else if(pid == 0){
        sleep(5);
        printf("%d\n",getppid());
        return 0;
    }
}