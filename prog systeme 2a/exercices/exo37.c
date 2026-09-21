#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>



int main(int argc, char *argv[]){

    int ret=-1;
    int pipefd[2];
    if (pipe(pipefd)==-1){
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    assert(pid!=-1);

    if(0==pid){
        //process enfant
        char* data= NULL;
        size_t recv =0;

        close(pipefd[1]);
        //char buff[128];

        ret = read(pipefd[0],&recv, sizeof(size_t));
        data= malloc(sizeof(char)*recv);
        assert(data);

        ret= read(pipefd[0],data, recv);
        assert(ret != -1);
        printf("moi je suis enfant, j'ai reçu:\n '%s'\n",data);

    }
    else if(pid>0){
        //process parent
        char *msg = "Bonjour tout le monde";


        close(pipefd[0]);
        size_t msg_size= strlen(msg)+1;

        ret= write(pipefd[1],&msg_size, sizeof(size_t));
        assert(ret !=-1);

        ret= write(pipefd[1],msg, strlen(msg)+1);
        assert(ret!=-1);

    }

    return 0;
}