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

    // On prépare un grand tableau pour stocker le message tapé
    char msg[128]; 

    while(1){
        char tmp2;
        int i = 0;

        // On lit sur stdin caractère par caractère comme dans votre exemple
        while (fread(&tmp2, sizeof(char), sizeof(char), stdin) > 0) {
            
            // Si l'utilisateur appuie sur Entrée, on arrête de lire pour ce message
            if (tmp2 == '\n') {
                break;
            }

            // Sinon, on ajoute le caractère dans notre tableau de message
            if (i < 127) { // Pour ne pas dépasser la taille du tableau
                msg[i] = tmp2;
                i++;
            }
        }

        // On termine proprement la chaîne de caractères avec un '\0'
        msg[i] = '\0';

        // On calcule la taille réelle à envoyer (+1 pour inclure le '\0')
        int size_to_send = strlen(msg) + 1;

        //first send msg size
        int ret = write(client_fd,&size_to_send,sizeof(int));
        die(ret,"on sending msg size");
        printf("SIZE SENT %d \n", size_to_send);

        //then send msg itself
        int sent_bytes = write(client_fd,msg,size_to_send);
        die(sent_bytes, "on sending");
        printf("msg sent (%s) (%d)\n", msg, size_to_send);
    }
    return 0;
}
