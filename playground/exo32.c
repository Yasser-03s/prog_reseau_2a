#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    pid_t pid= -1;
    pid= fork();
    assert(pid>-1);
    if (pid==0){ //pid>0 pour parent
        char *prog = "hello";
        char *argvexec[2];
        argvexec[0] = "hello";
        argvexec[1] = NULL;
        execv(prog, argvexec);
        fprintf(stderr,"Erreur Execv\n");
    }
    else if (pid>0){
        wait(NULL);
        exit(EXIT_SUCCESS);
        }
    
    
}
