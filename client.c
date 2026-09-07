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

//fonctions read_on_socket et write_on_socket


int read_on_socket(int socketfd, void *ptr, int size){

    int read_bytes = 0;
    int ret_value = 0;
    while (read_bytes != size){
        // CORRECTION : Remplacement de write par read pour lire sur la socket
        ret_value = read(socketfd, (char *)(ptr) + read_bytes, size - read_bytes);
        if (ret_value == 0){
            printf("Disconnected\n");
            exit(EXIT_FAILURE);
        }
        die(ret_value, "reading on socket");
        read_bytes += ret_value;
    }
    return 0;
}

int write_on_socket(int socketfd, void *ptr, int size){
    int written_bytes = 0;
    int ret_value = 0;
    while (written_bytes != size){
        ret_value = write(socketfd, (char *)(ptr) + written_bytes, size - written_bytes);
        if (ret_value == 0){
            printf("Disconnected\n");
            exit(EXIT_FAILURE);
        }
        die(ret_value, "writing on socket");
        written_bytes += ret_value;
    }
    return 0;
}




int main(int argc, char* argv[]){
    int client_fd = socket(AF_INET, SOCK_STREAM,0);
    die(client_fd, "socket creation");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    
    inet_aton("127.0.0.1", &server_addr.sin_addr); //ip config, ip addr
    
    int ret_value;
    ret_value = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    die(ret_value,"On connecting...");

    struct message mymsg;
    char data[128] = "Bonjour";
    mymsg.type = 0;
    mymsg.size = strlen(data)+1;
    mymsg.speaker_id = 123456789;

    // COMPLÉTION : Envoi de l'en-tête (header) de la structure message d'abord
    write_on_socket(client_fd, &mymsg, sizeof(struct message));

    // COMPLÉTION : Envoi des données (payload) juste après
    write_on_socket(client_fd, data, mymsg.size);

    // COMPLÉTION : Fermeture propre de la socket avant de quitter
    close(client_fd);

    return 0;
}
