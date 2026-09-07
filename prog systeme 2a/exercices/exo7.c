//Modifiez le programme précédent et rajoutez-y la lecture (et l’affichage) de l’entier que vous
//venez d’écrire dans le fichier.


//Écrivez un programme qui écrit un entier dans un fichier (i.e. pas sous forme de chaîne de
//caractères). Dans un terminal, affichez le contenu de ce fichier (à l’aide d’une commande shell
//comme cat, less ou more et non pas d’un programme C).

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd = -1;
    int value = 42;
    ssize_t ret = 0;
    int value2=0;

    
    fd = open("entier.txt",O_RDWR | O_CREAT, S_IRWXU);
    assert(fd > 0);

    ret = write(fd, &value, sizeof(value));
    assert(ret > 0);

    //close(fd);


    fd = open("entier.txt",O_RDWR | O_CREAT, S_IRWXU);
    assert(fd > 0);

    read(fd, &value2, sizeof(int));
    fprintf(stdout, "valeur lue = %i\n", value2);

    exit(EXIT_SUCCESS);
}