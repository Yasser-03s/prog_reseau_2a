#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    pid_t pid = -1;
    pid= fork();
    assert(pid!=-1);
    if(pid== 0){
        int fd = -1;
        fd= open("toto2.txt", O_RDWR |O_CREAT, S_IRWXU);
        assert(fd>0);
        char *argexecv[2]= {"fichier35",NULL};
        execv("fichier35",argexecv);
        fprintf(stdout, "Erreur d'exec\n");
    }
    else if(pid>0){wait(NULL);}
    exit(0);
}