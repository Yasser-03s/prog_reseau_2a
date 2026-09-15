#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>


int * mysort(int *tab){
    int tmp;
    bool flag = true;
    while (flag==true){
        flag=false;

        if (tab[0]>tab[1]){
            tmp=  tab[0];
            tab[0]=  tab[1];
            tab[1]= tmp;
            flag = true;
        }

        if (tab[1]>tab[2]){
            tmp=  tab[1];
            tab[1]=  tab[2];
            tab[2]= tmp;
            flag = true;
        }
            
        }
    return tab;
}


int main(int argc, char *argv[]){
    //process parent + boucle attent active
    //n process enfants + boucles active|passive de durée variable selon pid


    int k=6;
    pid_t pid1;
    pid_t pid2;
    pid_t pid3;
    pid_t   

    pid1 = fork();
    if (0!=pid1){
        pid2 = fork();
        if (0!= pid2){
            pid3 = fork();
            if (0!= pid3){
                do {int toto=0;
                while(++toto);
                printf("parent a fini l'attente\n");
                }while(0);
                

                }
            else{sleep(pid3%10);exit(103);}
        }
        else{sleep(pid2%10);exit(102);}
    }
    else{sleep(pid1%10);exit(101);}
    


}