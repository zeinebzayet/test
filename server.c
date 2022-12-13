#include "serv_cli.h"

int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread,i;
    struct sockaddr_in address;
    struct reponse r;
    struct question q;
    int opt = 1;
    int addrlen = sizeof(address);
    //char buffer[1024] = { 0 };
    //char* hello = "Hello from server";
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    /* initialisation du générateur de nombres aléatoires*/
    srand(getpid());

    valread = read(new_socket, &q, sizeof(q));

    /* Affichage du Question envoyé par le client */
    printf("\n****************** Question du Client numéro %d *****************\n",q.pidc);
    puts("\t     +------------------------------------------+");
    printf("\t     | Veuillez me générer %d nombres aléatoires |\n",q.quest);
    puts("\t     +------------------------------------------+");

    /* Construction de la réponse */
    r.pidserveur=getpid();
    for(i=0;i<q.quest;i++){
        r.rep[i] = rand() % (NMAX - 1) + 1;
    }

    send(new_socket, &r, sizeof(r), 0);
    printf("message sent\n");
 
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
