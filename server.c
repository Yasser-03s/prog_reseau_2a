#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
//#include <>

#define BACKLOG 10

struct message{
    int type; // RQ / RSP
    int size; // SIZE
    long int speaker_id;
};

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

    struct message client_msg = {0}; //je sais pas??

    //receive message size
    int ret = read(client_fd,&client_msg,sizeof(struct message));
    die(ret,"reception du header");
    printf("MSG HEADER (%d) (%d) (%ld) \n", client_msg.type, client_msg.size, client_msg.speaker_id);

    // on remplace cela char buf[128] = {0} par:
    char * data = malloc(sizeof(char) * client_msg.size);
    //receive message itself
    int return_val = read(client_fd,data,sizeof(struct message));
    die(return_val,"reception de data");
    printf("Le MSG est (%s)\n", data);
   return 0;

}