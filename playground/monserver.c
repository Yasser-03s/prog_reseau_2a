#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <errno.h>
#include <poll.h>
#define BACKLOG 10
#define MAX_CLIENTS 100




void die(int n,const char* msg){
    if(n<0){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    die(listen_fd,"creation de socket d'ecoute");
    
    int yes = 1;
    setsockopt(listen_fd,SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(1234);
    inet_aton("127.0.0.1",&server_addr.sin_addr);
    int ret_bind = bind(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    die(ret_bind,"on binding...");

    int ret_listen = listen(listen_fd, BACKLOG);
    die(ret_listen,"on listening...");

    struct pollfd fds[MAX_CLIENTS];
    nfds_t nfds=0;
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN;
    nfds++;
    
    for (int i=1; i<MAX_CLIENTS; i++){
        fds[i].fd = -1;
    }

    char buf[128]={0};


    while(1){
        int ret_poll = poll(fds,nfds,-1);
        die(ret_poll,"On polling...");
        for (int i=0;i<nfds;i++){

            if (fds[i].revents == 0){
                continue;
            }

            if (fds[i].fd == listen_fd){
                struct sockaddr_in client_addr = {0};
                socklen_t sizeofaddr = sizeof(client_addr);
                int client_fd = accept(listen_fd,(struct sockaddr *)&client_addr, &sizeofaddr);
                die(client_fd,"erreur client_fd");
                if(nfds == MAX_CLIENTS){printf("!! nbr max de clients atteint !!\n");}
                else{
                    fds[nfds].fd = client_fd;
                    printf("Connection établie avec client de fd %d\n", client_fd);
                    nfds++;
                }
            }

            else{

            }
            
        }

    }



    return 0;
}