#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    char *prog = "hello";
    char *argvexec[2];
    argvexec[0] = "hello";
    argvexec[1] = NULL;


    execv(prog, argvexec);
    fprintf(stdout,"Erreur d'exec\n");
}
