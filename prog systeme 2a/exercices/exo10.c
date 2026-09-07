//Écrivez un programme qui ouvre un fichier avec la fonction fopen puis qui ouvre un fichier (le
//même ou un autre, peu importe) avec l’appel-système open. Affichez la valeur de l’index de
//descripteur associé.
//— Que constatez-vous ?
//— Que pouvez-vous en déduire ?



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fp=NULL;
    int fd = -1;
    
    fp=fopen("toto.txt", "w+");
    assert (fp);

    fd = open("toto.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    assert(fd >0);

    printf(" l'index du descripteur 'open' est %d\n",fd);
    return 0;
}