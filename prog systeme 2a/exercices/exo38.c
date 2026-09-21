#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>



int main(int argc, char *argv[]){

    int ret=-1;
    char* path= "mon tube";
    mkfifo(path, S_IRUSR | S_IWUSR);
    int fd=-1;

    int pid = fork();
    assert(pid!=-1);

    if(0==pid){
        //process enfant
        char* data= NULL;
        size_t recv =0;

        fd= open(path, O_RDONLY);
        assert(fd!=-1);
        //char buff[128];

        ret = read(fd,&recv, sizeof(size_t));
        data= malloc(sizeof(char)*recv);
        assert(data);

        ret= read(fd,data, recv);
        assert(ret != -1);
        printf("moi je suis enfant, j'ai reçu:\n '%s'\n",data);
        free(data);
        close(fd);

    }
    else if(pid>0){
        //process parent
        char *msg = "Bonjour tout le monde";

        fd=open(path, O_WRONLY);
        assert(fd != -1);
        
        size_t msg_size= strlen(msg)+1;

        ret= write(fd,&msg_size, sizeof(size_t));
        assert(ret !=-1);

        ret= write(fd,msg, strlen(msg)+1);
        assert(ret!=-1);

        close(fd);

    }

    return 0;
}