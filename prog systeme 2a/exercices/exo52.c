#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void* routine(void *arg){
    int value = *((int *)arg);
    printf("1: Je suis appelée %i!\n", value);
    return NULL;
}

int main(int argc, char *argv[]){
    pid_t pid= getpid();
    printf("main pid: %i\n", pid);
    int ret= -1;
    int arg[2]= {10, 20};
    pthread_t thread1;
    ret= pthread_create(&thread1,NULL, routine, &arg[0]);
    assert(ret!= -1);
    pthread_t thread2;
    ret= -1;
    ret = pthread_create(&thread2,NULL, routine, &arg[1]);
    assert(ret!= -1);
    sleep(1);
    return 0;
}

