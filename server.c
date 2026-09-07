#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h> // Ajout pour la cohérence

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

// Inclusions des fonctions demandées
int read_on_socket(int socketfd, void *ptr, int size){
    int read_bytes = 0;
    int ret_value = 0;
    while (read_bytes != size){
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
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    die(listen_fd, "creation socket serveur");

    int yes=1;
    setsockopt(listen_fd,SOL_SOCKET, SO_REUSEADDR,&yes, sizeof(yes));

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(1234);

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
    
    // COMPLÉTION : Utilisation de die pour vérifier l'échec d'accept
    die(client_fd, "On accepting...");
    printf("New client accepted, and new socket fd is %d\n", client_fd);

    struct message client_msg = {0}; 
        
    // COMPLÉTION : Remplacement du read brut par read_on_socket pour le header
    int return_val = read_on_socket(client_fd, &client_msg, sizeof(struct message));
    printf("MSG HEADER (%d) (%d) (%ld) \n", client_msg.type, client_msg.size, client_msg.speaker_id);

    // Allocation dynamique du buffer selon la taille reçue dans le header
    char * data = malloc(sizeof(char) * client_msg.size);
    if (data == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // COMPLÉTION / CORRECTION : Utilisation de la bonne fonction et des bonnes variables
    return_val = read_on_socket(client_fd, data, client_msg.size);
    printf("Le MSG est (%s)\n", data);

    // Nettoyage et fermeture des ressources
    free(data);
    close(client_fd);
    close(listen_fd);

    return 0;
}
