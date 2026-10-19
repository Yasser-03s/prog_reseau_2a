//envoyer numero avec un signal à l'aide de sigqueue
// exo3 est page 89

#define _POSIX_C_SOURCE 199309L


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

int protocol_receive(int fd, char* buff, size_t length){
    int ret= -1;
    int received= 0;
    do{
        ret= read(fd, (char*)buff + received, length-received);
        assert(ret!= -1);
        received+= ret;
    }while(received< length);
    return 1;
}

int main(int argc, char* argv[]){
    //chercher le pid du serveur
    int fd_pid_server= -1;
    char pid_server[128];
    fd_pid_server= open("/TMP/serverPID", O_RONLY);
    assert(fd_pid_server!= -1);
    assert(protocol_receive(fd_pid_server, pid_server, 128));
    printf("%s", pid_server);

    //creation des tubes
    pid_t pid= getpid();
    //pipe1 pour ecriture
    char nom_pipe1[128];
    //pipe2 pour lecture
    char nom_pipe2[128];
    sprintf(nom_pipe1, "/tmp/PIPE_%ld_numéro1", pid);
    sprintf(nom_pipe2, "/tmp/PIPE_%ld_numéro2", pid);
    assert(mkfifo(nom_pipe1, O_RDONLY)>0);
    assert(mkfifo(nom_pipe2, O_WRONLY)>0);
    
    //client va envoyer au serveur un signal de type SIGUSR1, avec deux numéros qui vont
    //permettre d’identifier deux tubes nommés
    union sigval id;
    id.sival_int= 12;
    int ret= -1;
    ret= sigqueue(pid_server, SIGUSR1, id);
    if (ret == -1){
        perror("sigqueue failure..\n");
    }
}