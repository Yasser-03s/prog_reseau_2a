#include <signal.h>

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]){
    kill(atoi(argv[1]), SIGKILL);
    exit(EXIT_SUCCESS);
}