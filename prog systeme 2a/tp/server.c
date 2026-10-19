//definir une limite de clients?
//le pid doit etre connu.. je le met dans un fichier tmp
//cree un processus par client 



#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CLIENT_MAX= 10

int protocol_send(int fd, char* buffer, int length){
    int written= 0;
    int ret= -1;
    do{
        ret= write(fd, (char*)buffer+written, length-written);
        assert(ret!= -1);
        written+= ret;
    } while(written!= length);
    return 1;
}


int main(int argc, char* argv[]){
    char pid[128];
    sprintf(pid,"%d"+'\0',getpid());
    int length= strlen(pid);
    int fd_pid= -1;
    fd_pid= open("/TMP/serverPID", O_WRONLY|O_CREAT, S_IRWXU);
    assert(fd_pid >0);
    assert(protocol_send(fd_pid ,pid, length));
    close(fd_pid);


    return 0;
}