#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
//#include <>


void die(int ret_value, const char*msg){
    if (ret_value<0){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char* argv[]){
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    die(listen_fd, "creation socket serveur");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(1234);
    //server_addr.sin_addr

    inet_aton("127.0.0.1 ", &server_addr.sin_addr);


    int ret_bind = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    die(ret_bind,"On binding...");
    
    int BACKLOG;
    int ret_listen = listen(listen_fd, BACKLOG);
    die(ret_listen,"On listening...");

    struct sockaddr_in client_addr = {0};
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=htons(1234);

    socklen_t sizeofaddr = 0;
    printf("start accepting...\n");
    int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,sizeofaddr);
    if (client_fd != -1){
        printf("New client accepted, and new socket fd is %d\n", client_fd);
    }
    return 0;

}