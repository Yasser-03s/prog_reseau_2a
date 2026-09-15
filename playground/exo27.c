#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int fd = open("toto.txt", O_RDWR | O_CREAT);

    assert(fd>0);
    pid_t pid= fork();

    struct message{
        int sender_id;
        int size;
    };

    pid_t pid_termine;
    int status;

    if (0!= pid){
        do{int toto = 0;
        while(++toto);
        printf("je suis papa j'ai fini\n");
        }while(0);
        pid_termine = wait(&status);
        printf("parent: filspid= %d\n",pid_termine);
        printf("code de retours fils= %d\n", WEXITSTATUS(status));
    }

    else{

        printf("fils : perepid= %d\n", getppid());
        printf("fils : mon pid= %d\n", getpid());
        sleep(5);
        exit(67);
    }

    
    close(fd);
}