#include <semaphore.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>


#define NTHREADS 2
// 2 threads se partages un buffer d'un seul caractère



//semaphores et buffer declarés comme variable globales:
char shared_buffer;
sem_t sem_prod;
sem_t sem_cons;
    

void *function(void *arg){
    int index= *(int *)arg;
    int i;
    if (index == 0){
        for (i=0; i<26; i++){
            sem_wait();
            fprintf(stdout, "Ecriture %c", shared_buffer);

        }
    }
    else if(index == 1){
        for (i=0; i<26; i++){
            sem_wait();
            fprintf(stdout, "Lecture %c", shared_buffer);

        }
    }
}

int main(int argc, char* argv[]){

    pthread_t threads[NTHREADS];
    int args[NTHREADS];

    sem_init(&sem_prod,0,1);
    sem_init(&sem_cons,0,1);

    for (int index=0; index< NTHREADS; index++){
        pthread_create(&threads[NTHREADS], NULL, function, (void *)args[index]);
    }

    exit(EXIT_SUCCESS);
}