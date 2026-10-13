#include <semaphore.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define NPROCS 10




int main(int argc, char* argv[]){
    pid_t pids[NPROCS];
    int index= 0;

    char *addr = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1 , 0);
    assert(addr != MAP_FAILED);

    sem_t sem;
    sem_int(&sem,1 , 0);
    for (index =0; index < NPROCS; index++){
        sem_wait(&sem);
        
    }
}