#include <stdio.h> //bibliothèque entrée sortie standard perror: traduit errno to man explanation
#include <unistd.h> //pour pouvoir fermer avec close()
#include <stdlib.h> //pour exit() malloc() free() atoi()..
#include <sys/socket.h> //pour sockets, faire man socket pour voir les valeurs possibles
#include <errno.h> 

int main(int argc, char *argv[]) {
    int server_socket;
    int client_socket;
    server_socket = socket(AF_INET,SOCK_STREAM, 0);//faire man socket pour remplacer les variables
    //generalement AF_INET pour IPv4 et SOCK_STREAM et 0 pour protocole
    
}
