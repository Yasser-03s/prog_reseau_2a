#include <stdio.h> //bibliothèque entrée sortie standard perror: traduit errno to man explanation
#include <unistd.h> //pour pouvoir fermer avec close()
#include <stdlib.h> //pour exit() malloc() free() atoi()..
#include <sys/socket.h> //pour sockets, faire man socket pour voir les valeurs possibles
#include <errno.h> 
#include <arpa/inet.h> //pour inet_aton
#include <string.h> //pour strlen


void die(int ret_value, const char*msg){
    if(ret_value<0){
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

struct message{
    int type; // RQ / RSP
    int size; // SIZE
    long int speaker_id;
};

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

    struct message mymsg;
    char data[128] = "Bonjour";
    mymsg.type = 0;
    mymsg.size = strlen(data)+1;
    mymsg.speaker_id = 123456789;

    //First send message header
    //int ret=write(client_fd, &mymsg,sizeof(struct message));
    //die(ret, "envoi du header");
    int written_bytes = 0;
    int to_write = sizeof(struct message);
    while (written_bytes != to_write){
        ret_value = write(client_fd, (char *)&mymsg + written_bytes, to_write - written_bytes);
        if (ret_value == 0){
            printf("Disconnected\n");
            exit(EXIT_FAILURE);
        }
        die(ret_value, "reading msg header");
        written_bytes += ret_value;
    }

    //then send the data itself
    int ret_val = write(client_fd, data, mymsg.size);
    die(ret_val,"envoi data");

    return 0;
}
