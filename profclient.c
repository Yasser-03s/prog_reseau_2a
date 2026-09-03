#include <stdio.h> //bibliothèque entrée sortie standard perror: traduit errno to man explanation
#include <unistd.h> //pour pouvoir fermer avec close()
#include <stdlib.h> //pour exit() malloc() free() atoi()..
#include <sys/socket.h> //pour sockets, faire man socket pour voir les valeurs possibles
#include <errno.h> 
#include <arpa/inet.h> //pour inet_aton

void die(int ret_value, const char*msg){
    if(ret_value<0){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char* argv[]){
    int client_fd = socket(AF_INET, SOCK_STREAM,0);
    die(client_fd, "socket creation");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    //server_addr.sin_addr
    inet_aton("127.0.0.1", &server_addr.sin_addr); //ip config, ip addr
    //aton ascii to network, pton presentation to network (plus moderne) la diff est pton donne l
    int ret_value;
    ret_value = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    //?? operation cast (struct sockaddr *)&server_addr
    die(ret_value,"On connecting...");
    return 0;
}
