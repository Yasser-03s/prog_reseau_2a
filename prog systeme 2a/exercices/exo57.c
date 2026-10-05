#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define N 10

void *fonction(void* arg){
    int value = *((int *)arg);
    printf("Je suis appelée par indice %i je quit mtn!\n", value);
    return value;
}


int main(int argc, char * argv[]){
    printf("main pid: %i\n", getpid());
    int ret;
    int args[N]={0};
    pthread_t thread[N];
    for (int i=0; i<N; i++){
        ret= -1;
        args[i]=i;
        ret= pthread_create(thread+i,NULL, fonction, (int *)&args[i]);
        assert(ret!= -1);
    }
    int k = 0;
    for (int i=0; i<N; i++){
        void *valeur;
        pthread_join(thread[i], &valeur);
        k= k+(int)(long)valeur;
    }
    printf("========= le resultat est %i (expectedd %i) =========\n", k, 0+1+2+3+4+5+6+7+8+9);
    return 0;
}