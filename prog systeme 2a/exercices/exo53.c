#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define N 10

void *fonction(void* arg){
    int value = *((int *)arg);
    printf("Je suis appelée par indice %i!\n", value);
    return NULL;
}


int main(int argc, char * argv[]){
    printf("main pid: %i\n", getpid());
    int ret;
    int args[N]={0};
    pthread_t thread[N];
    for (int i=0; i<N; i++){
        ret= -1;
        args[i]=i;
        ret= pthread_create(thread+i,NULL, fonction, (void *)&args[i]);
        assert(ret!= -1);
    }
    sleep(2);
    return 0;
}