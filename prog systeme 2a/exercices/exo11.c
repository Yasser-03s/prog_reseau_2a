//Exercice 12 (⋆)
//Écrivez un programme qui redirige tous ses appels à fprintf(stdout, ...) dans un fichier
//output.txt plutôt que sur sa sortie standard, sans modifier les appels à fprintf dans le
//programme d’origine et sans utiliser des (index de) descripteurs de fichiers ni la duplication.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *fp = NULL;

    fp = freopen("output.txt", "w", stdout);
    assert (fp!=NULL);
    fprintf(stdout, "un petit teste\n");
    fclose(fp);
    exit(EXIT_SUCCESS);

}