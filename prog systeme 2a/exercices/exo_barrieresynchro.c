//implementation de barriere de synchro entre threads avec moniteurs
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int             count;
}my_barrier_t;


int my_barrier_init(my_barrier_t *barrier, const int num_threads){
    barrier->count = num_threads;
    pthread_mutex_init(&(barrier->mutex), NULL);
    pthread_cond_init(&(barrier->cond), NULL);
    return 0;
}


int my_barrier_wait(my_barrier_t *barrier){
    pthread_mutex_lock(&(barrier->mutex));  //et pas 

    if (--barrier->count <= 0){
        pthread_cond_broadcast(&(barrier->cond));
    }
    else{
        while(barrier->count >0)
            pthread_cond_wait(&(barrier->cond), &(barrier->mutex)) ;
    }
    barrier->count--;
    pthread_mutex_unlock(&(barrier->mutex));
    return 0;
}

int maint(int argc, char* argv){

}