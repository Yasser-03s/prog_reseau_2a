//Écrivez un programme qui redirige tous ses appels à printf dans un fichier output.txt plutôt
//que sur sa sortie standard, sans modifier les appels à printf dans le programme d’origine.


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){

    int fd = -1;
    int ret = -1;
    fd = open("output.txt", O_RDWR | O_CREAT, S_IRWXU);
    assert(fd > 0);


    close(STDOUT_FILENO);
    ret = dup(fd);
    close(fd);
    assert (ret >0);

    printf("Hello world\n");
    exit(EXIT_SUCCESS);
}