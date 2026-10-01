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

    //construction du mask
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    int ret = sigprocmask(SIG_SETMASK,&mask,SIGUSR1);
    assert(ret != -1);

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = traitant;

    sigaction(SIGUSR1, &act, NULL);
 
    pause();

    sigaction(SIGUSR1, &act, NULL);
 
    pause();


    exit(EXIT_SUCCESS);
    
}