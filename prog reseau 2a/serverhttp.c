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



int read_http_rq(int fd, char *buf, int buf_size){
    int i= 0;
    while(i < buf_size - 1){
        int n = read(fd, &buf[i], 1);
        die(n,"read_http");
        if(n == 0){
            return 0;
        }
        i++;
        buf[i]= '\0';
        if(i >= 4 && strcmp(&buf[i - 4], "\r\n\r\n") == 0)
            return i;
    }
    return 0;
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
    
 
    die(client_fd, "On accepting...");
    printf("New client accepted, and new socket fd is %d\n", client_fd);


    char request[4096] = {0};
    read_http_rq(client_fd, request, 4096);
    
    printf("Le MSG est (%s)\n", request);

//    char * response = "Ceci est un Test";
//    int ret_wr = write_on_socket(client_fd,response ,strlen(response));
//    die(ret_wr, "on writing..");


    char response[4096];
    char html_body[]="<html><body><h1>Hello, world!</h1></body></html>";

    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/html\r\n\r\n%s", strlen(html_body), html_body);
    write_on_socket(client_fd, response, strlen(response));

    close(client_fd);
    close(listen_fd);

    return 0;
}