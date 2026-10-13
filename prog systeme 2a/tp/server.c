//definir une limite de clients?
//le pid doit etre connu.. je le met dans un fichier tmp
//cree un processus par client 



#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>




int main(int argc, char* argv[]){
    pid_t pid= getpit();
    assert(open("/serverPID", )>0);

}