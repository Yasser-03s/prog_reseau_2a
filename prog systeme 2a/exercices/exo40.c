//exo 40 et 41 avec modif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

//Créez un programme avec deux processus qui se partagent de la mémoire pour s’échanger des
//données (une chaîne de caractères par exemple) en utilisant un fichier en support.

int main(int argc, char *argv[]){
    int fd =-1;
    int ret = -1;
    //fd = open("support",O_RDWR | O_CREAT, S_IRWXU);
    //assert(fd != -1);
    off_t taille = sysconf(_SC_PAGE_SIZE);
    //ret = ftruncate(fd, taille);
    //assert(ret != -1);
    
    char *ptr = mmap(NULL,taille,PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,-1, 0); 
    assert(ptr != MAP_FAILED); 
    //assert(fd != -1);
    pid_t pid = -1;
    pid_t pid2 = -1;
    pid = fork();
    if (0==pid){ // enfant0=parent1
        pid2 = fork();
        if (0==pid2){ //enfant 1 écrivain
            char *msg= "Bonjour\0";
            //char *ptr = mmap(NULL,taille,PROT_WRITE,MAP_SHARED,fd,0);
            //assert(ptr != MAP_FAILED);
            char *current = ptr;
            memcpy(current,msg,strlen(msg)+1);
            munmap(ptr,taille);
        }
        else if (0!=pid2){ //enfant 0
            //char *ptr2 = mmap(NULL,taille,PROT_READ,MAP_SHARED,fd,0);
            //assert(ptr2 != MAP_FAILED);
            printf("reçu: %s",ptr);
            waitpid(pid2,NULL,0);
            munmap(ptr,taille);
        }
    }
    else if (0!=pid){
        waitpid(pid,NULL,0);
    }
    
    close(fd);
}