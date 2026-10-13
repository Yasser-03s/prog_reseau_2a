//envoyer numero avec un signal à l'aide de sigqueue
// exo3 est page 89



#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>



int main(int argc, char* argv[]){
    pid_t pid= getpid();
    //pipe1 pour ecriture
    char nom_pipe1[128];
    //pipe2 pour lecture
    char nom_pipe2[128];
    sprintf(nom_pipe1, "/tmp/PIPE_%ld_numéro1", pid);
    sprintf(nom_pipe2, "/tmp/PIPE_%ld_numéro2", pid);
    assert(mkfifo(nom_pipe1, O_RDONLY)>0);
    assert(mkfifo(nom_pipe2, O_WRONLY)>0);
    
}