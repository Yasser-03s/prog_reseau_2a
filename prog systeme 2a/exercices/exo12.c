//Écrivez un programme qui lit l’intégralité d’un fichier, caractère par caractère (i.e. octet par
//octet) et qui affiche le tout sur sa sortie standard d’erreur.
//N.B L’utilisation de stat ou fstat n’est pas autorisée pour cet exercice.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("entrez un chemin valide!.... \n");
    }

    int fd=-1;
    FILE *fp = NULL;
    char tmp;

    fd = open(argv[1], O_RDONLY);
    assert(fd>0);

    while(read(fd,&tmp,))

        fprintf(stdout, );

}