#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h> // Ajout pour la cohérence
#include <poll.h>

#define FDS_SIZE 100
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


    struct pollfd fds[FDS_SIZE];
    fds[0].fd=listen_fd;
    fds[0].events=POLLIN;
    fds[0].revents=0;

    for(int i=1; i<FDS_SIZE; i++){
        fds[i].fd = -1;
        fds[i].events = 0;
        fds[i].revents = 0;
    }

    int k = 1;

    while(1){
        printf("waiting for activity..");
        int nb_active_fd = poll(fds, FDS_SIZE, -1);
        die(nb_active_fd, "On polling...");
        for (int i=0 ; i<FDS_SIZE; i++){
            if(i == 0 && fds[0].revents & POLLIN){
                fds[i].revents = 0;
                int client_fd = accept(listen_fd,NULL,NULL);
                die(client_fd, "accept");
                for (size_t j=0; j < FDS_SIZE;j++);
            }
            else if (fds[i].events & POLLIN){
                fds[i].revents=0;
                struct message msg = {0};
                int ret = read_on_socket(fds[i].fd, &msg, sizeof(msg));
                if (ret ==0){
                    close(fds[i].fd);
                    fds[i].fd = -1;
                    fds[i].events = POLLIN;
                    fds[i].revents = 0;
                }
            }
        }

    }






    //printf("start accepting...\n");
    //int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr,&sizeofaddr);
    //
    //// COMPLÉTION : Utilisation de die pour vérifier l'échec d'accept
    //die(client_fd, "On accepting...");
    //printf("New client accepted, and new socket fd is %d\n", client_fd);
//
    //struct message client_msg = {0}; 
    //    
    //// COMPLÉTION : Remplacement du read brut par read_on_socket pour le header
    //int return_val = read_on_socket(client_fd, &client_msg, sizeof(struct message));
    //printf("MSG HEADER (%d) (%d) (%ld) \n", client_msg.type, client_msg.size, client_msg.speaker_id);
//
    //// Allocation dynamique du buffer selon la taille reçue dans le header
    //char * data = malloc(sizeof(char) * client_msg.size);
    //if (data == NULL) {
    //    perror("malloc failed");
    //    exit(EXIT_FAILURE);
    //}
//
//
    //return_val = read_on_socket(client_fd, data, client_msg.size);
    //printf("Le MSG est (%s)\n", data);














    // Nettoyage et fermeture des ressources
    //free(data);
    //close(client_fd);
    close(listen_fd);

    return 0;
}
