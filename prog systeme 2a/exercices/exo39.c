#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>



int main(int argc, char *argv[]){
    int ret=!-1;
    int fd=-1;
    //cat toto.txt | grep"truc" | wc -l 
    fd= open("toto.txt",O_RDONLY);
    assert(fd !=-1);

    int tube1[2];
    assert(pipe(tube1)!=-1);
    
    pid_t enfant1= -1;
    pid_t enfant2= -1;
    
    enfant1= fork();
    assert(enfant1 != -1);

    if(enfant1 > 0){
        //parent
        close(tube1[1]);

        //Redirection STDIN
        close(STDIN_FILENO);
        dup(tube1[0]);
        close(tube1[0]);

        execlp("wc","wc","-l","NULL");


    }

    else if (0==enfant1){
        //enfant1
        close(tube1[0]);

        int tube2[2];
        assert(pipe(tube2)!=-1);

        enfant2=fork();
        assert(enfant2 != -1);

        if (enfant2>0){// code du parent (grep)
            close(tube2[1]);
            
            //Redirection STDIN
            close(STDIN_FILENO);
            dup(tube1[0]);
            close(tube1[0]);

            //Redirection STDOUT
            close(STDOUT_FILENO);
            dup(tube2[1]);
            close(tube2[1]);

            execlp("grep","grep","truc","NULL");
        }
        else if (0==enfant2){ //code del'enfant (cat)
            close(tube2[1]);
            close(tube1[0]);

            //Redirection STDOUT
            close(STDOUT_FILENO);
            dup(tube2[1]);
            close(tube2[1]);

            execlp("cat","cat","toto.txt","NULL");
        }
    }
    return 0;

}