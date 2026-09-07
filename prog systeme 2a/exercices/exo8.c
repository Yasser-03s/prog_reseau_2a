//Écrivez un programme qui écrit n caractères dans un fichier. Les arguments du programme
//seront le nom du fichier et la valeur de n. Le i-ème caractère devra être écrit à la position 2 i dans
//le fichier, en supposant que la numérotation des caractères commence à 1.



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){


    int fd=-1;
    ssize_t ret = 0; //toujours initier ssize avant de write
    off_t pos=2;


    if (argc != 3){
        fprintf(stderr, "entrez <nom_ficher> <valeur_de_n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *nom_fichier = argv[1];
    int n=atoi(argv[2]);

    fd = open(nom_fichier,O_RDWR | O_CREAT | O_TRUNC, S_IRWXU); 
    assert(fd>0);

    for (int i=1; i<=n; i++, pos*=2){
        char c = 'A' + (i - 1) % 26; 
        off_t offset = lseek(fd, pos, SEEK_SET);
        assert(offset >0);
        ret = write(fd, &c, sizeof(char));
    }   

    
    return 0;
}