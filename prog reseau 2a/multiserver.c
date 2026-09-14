#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <poll.h> // 1. AJOUT de la bibliothèque pour poll()

#define BACKLOG 10
#define MAX_CLIENTS 100 // Nombre maximum de clients connectés en même temps

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
    inet_aton("127.0.0.1", &server_addr.sin_addr);

    int ret_bind = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    die(ret_bind,"On binding...");
    
    int ret_listen = listen(listen_fd, BACKLOG);
    printf("mon listen fd est %d\n",listen_fd);
    die(ret_listen,"On listening...");

    // 2. CONFIGURATION DE POLL
    // On crée un tableau de structures pollfd pour surveiller nos sockets
    struct pollfd fds[MAX_CLIENTS];
    int nfds = 0; // Nombre actuel de sockets surveillées

    // On commence par surveiller la socket d'écoute (le serveur lui-même)
    fds[0].fd = listen_fd;
    fds[0].events = POLLIN; // On veut savoir quand un nouveau client veut se connecter
    fds[0].revents = 0;
    nfds++;

    // On initialise le reste du tableau à -1 (vide)
    for (int i = 1; i < MAX_CLIENTS; i++) {
        fds[i].fd = -1;
    }

    printf("Serveur démarré, en attente d'événements...\n");

    char buf[128] = {0};

    // 3. BOUCLE PRINCIPALE AVEC MULTIPLEXAGE
    while(1){
        // poll() attend qu'un événement se produise sur une des sockets (-1 signifie pas de timeout)
        int ret_poll = poll(fds, nfds, -1);
        die(ret_poll, "Erreur sur poll");

        // On parcourt toutes les sockets surveillées pour voir laquelle a bougé
        int current_size = nfds; 
        for (int i = 0; i < current_size; i++) {
            
            // Si rien ne s'est passé sur cette socket, on passe à la suivante
            if (fds[i].revents == 0)
                continue;

            // CAS 1 : C'est la socket du SERVEUR -> Un NOUVEAU client arrive
            if (fds[i].fd == listen_fd) {
                struct sockaddr_in client_addr = {0};
                socklen_t sizeofaddr = sizeof(client_addr);
                
                int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &sizeofaddr);
                if (client_fd < 0) {
                    perror("accept");
                    continue;
                }

                printf("Nouveau client accepté, fd: %d\n", client_fd);

                // On ajoute ce nouveau client dans notre tableau poll
                if (nfds < MAX_CLIENTS) {
                    fds[nfds].fd = client_fd;
                    fds[nfds].events = POLLIN; // On veut savoir quand ce client envoie des données
                    nfds++;
                } else {
                    printf("Trop de clients connectés, refusé.\n");
                    close(client_fd);
                }
            } 
            
            // CAS 2 : C'est la socket d'un CLIENT -> Il a envoyé un message (ou s'est déconnecté)
            else {
                int client_fd = fds[i].fd;
                int next_msg_size = 0;

                // On lit d'abord la taille du message
                int ret_size = read(client_fd, &next_msg_size, sizeof(int));
                
                // Si read renvoie 0 ou moins, le client s'est déconnecté ou il y a une erreur
                if (ret_size <= 0) {
                    if (ret_size == 0) {
                        printf("Client fd %d déconnecté\n", client_fd);
                    } else {
                        perror("Erreur lecture taille");
                    }
                    close(client_fd);
                    fds[i].fd = -1; // On libère la place dans poll
                } 
                // Sinon, on lit le message lui-même
                else {
                    printf("[Client %d] Taille reçue: %d\n", client_fd, next_msg_size);
                    
                    int read_bytes = read(client_fd, buf, 128);
                    if (read_bytes <= 0) {
                        printf("Client fd %d déconnecté pendant la lecture du msg\n", client_fd);
                        close(client_fd);
                        fds[i].fd = -1;
                    } else {
                        printf("[Client %d] Message reçu: (%s) (%d octets)\n", client_fd, buf, read_bytes);
                    }
                }
            }
        }

        // Nettoyage optionnel du tableau poll (on tasse le tableau pour enlever les fd à -1)
        for (int i = 0; i < nfds; i++) {
            if (fds[i].fd == -1) {
                for (int j = i; j < nfds - 1; j++) {
                    fds[j] = fds[j + 1];
                }
                nfds--;
                i--;
            }
        }
    }
    
    close(listen_fd);
    return 0;
}
