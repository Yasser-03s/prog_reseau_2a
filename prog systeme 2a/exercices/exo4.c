//Créez un fichier dans votre répertoire de travail (avec une commande shell). Écrivez un
//programme qui ouvre ce fichier et affiche la valeur (de l’index) de descripteur de fichier. Cette
//valeur est-elle conforme à vos attentes ?


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> //pour close()


int main(int argc, char *argv[]){


    int fd = open("test",O_RDONLY);
    //ne pas oublier close

    if (fd == -1){
        perror("echec de l'ouverture");
        exit(EXIT_FAILURE);
    } //pour check


    printf("%d\n",fd);
    close(fd);
    exit(EXIT_SUCCESS);
}