#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
//#include <>
#define BACKLOG 10

void die(int ret_value, const char*msg){
    if (ret_value<0){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char* argv[]){
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    die(listen_fd, "creation socket serveur");

    int yes=1;
    setsockopt(listen_fd,SOL_SOCKET, SO_REUSEADDR,&yes, sizeof(yes));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(1234);
    //server_addr.sin_addr

    inet_aton("127.0.0.1", &server_addr.sin_addr);


    int ret_bind = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    die(ret_bind,"On binding...");
    
    int ret_listen = listen(listen_fd, BACKLOG);
    die(ret_listen,"On listening...");

    struct sockaddr_in client_addr = {0};
    client_addr.sin_family=AF_INET;

    socklen_t sizeofaddr = sizeof(client_addr);
    printf("start accepting...\n");
    int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,&sizeofaddr);
    if (client_fd != -1){
        printf("New client accepted, and new socket fd is %d\n", client_fd);
    }

//read from socket
    int read_bytes = 0;
    char buf[128] = {0};
    int next_msg_size = 0;

//first recv the next msg size
    int ret = read(client_fd,&next_msg_size, sizeof(int));
    die(ret,"on reading msg size\n");
    printf("SIZE RCV %d\n", next_msg_size);
//then recv the message itself  

    read_bytes = read(client_fd,buf, 128);
    die(read_bytes,"On reading");
    printf("msg received: (%s) (%d)\n",buf, read_bytes);
    return 0;

}