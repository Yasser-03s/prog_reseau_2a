#include <signal.h>


#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]){
    for (int i=0 ; i<10 ; i++){
        kill(atoi(argv[1]),SIGUSR1);
    }
}