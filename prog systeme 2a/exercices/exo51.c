#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void* routine(void *arg){
    printf("1: Je suis appelée!\n");
    return NULL;
}

void* routine2(void *arg){
    printf("2: Je aussi suis appelée!\n");
    return NULL;
}

int main(int argc, char *argv[]){
    pid_t pid= getpid();
    printf("main pid: %i\n", pid);
    int ret= -1;
    pthread_t thread1;
    ret= pthread_create(&thread1,NULL, routine, NULL);
    assert(ret!= -1);
    pthread_t thread2;
    ret= -1;
    ret = pthread_create(&thread2,NULL, routine2, NULL);
    assert(ret!= -1);
    sleep(1);
    return 0;
}