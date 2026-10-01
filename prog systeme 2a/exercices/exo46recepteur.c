#include <signal.h>


#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

void traitant(int signum){
    printf("j'ai reçu le signal %d.\n", signum);
}

int main(int argc, char* argv[]){

    fprintf(stdout,"=== Mon pid est ==== %d\n", getpid());


    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = traitant;

    sigaction(SIGUSR1, &act, NULL);
    while(1){
        //pause
    }
    exit(EXIT_SUCCESS);
    
}