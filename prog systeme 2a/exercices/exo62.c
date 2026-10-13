#include <semaphore.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

#define NPROCS 10


int main(int argc, char* argv[]){
    pid_t pids[NPROCS];
    sem_t *semaphore= sem_open("/mon_sem", O_RDWR|O_CREAT, S_IRWXU, 0);
    unsigned int value=0;
    int k=0;
    for (int i=0; i<NPROCS;i++){ //creation de 10 processus enfants
        pids[i]= fork();
        if(0 == pids[i]){
            assert(sem_post(semaphore)>0);
            k++;
            break;
        }
    }
    if(0 != pids[i]){
        wait(NULL);
        assert(sem_wait(semaphore)>0);
    }
    
    return 0;
}

//a debugger....