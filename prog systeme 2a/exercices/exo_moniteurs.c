//implementation de semaphore avec moniteurs
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

//Structure de semaphore
typedef struct moniteur_semaphore{
    pthread_mutex_t  mutex;
    pthread_cond_t   cond;
    int              jetons;

}my_sem_t;

//INIT()
void *Initialiser_jettons(my_sem_t *sem, int value){
    sem->jetons = value;
    pthread_mutex_init(&(sem->mutex), NULL);
    pthread_cond_init(&(sem->cond), NULL);
}

//P()
int Prendre_jetton(my_sem_t *sem){
    pthread_mutex_lock(&(sem->mutex));  //et pas 

    while (sem->jetons == 0){
        pthread_cond_wait(&(sem->cond), &(sem->mutex)) ;
    }
    sem->jetons--;
    pthread_mutex_unlock(&(sem->mutex));
}

//V()
int Remettre_jetton(my_sem_t *sem){
    pthread_mutex_lock(&(sem->mutex));

    sem->jetons++;
    pthread_mutex_unlock(&(sem->mutex));
}

int main(int argc, char* argv[]){

    return 0;
}