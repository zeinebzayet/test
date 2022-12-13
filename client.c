#include "serv_cli.h"
 
int main(int argc, char const* argv[])
{
    int sock = 0, valread, client_fd,nb,i;
    struct sockaddr_in serv_addr;
    struct question q;
    struct reponse r;
    char buffer[1024] = { 0 };

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }


    /* initialisation du générateur de nombres aléatoires*/
    srand(getpid());

    /* Construction et envoi d’une question */
    nb=rand() % (NMAX - 1) + 1;
    q.pidc=getpid();
    q.quest=nb;

    send(sock, &q, sizeof(q), 0);
    printf("Message sent\n");


    valread = read(sock, &r, sizeof(r));
    /* Traitement local de la réponse */
    printf("\n********************* Réponse du Serveur numéro %d ************************\n\n",r.pidserveur);
    printf("Les %d nombres aléatoires générés : \n\n ",nb);
    for(i=0;i<nb;i++){
        printf("%d | ",r.rep[i]);
    }

    printf("\n");
 
    // closing the connected socket
    close(client_fd);
    return 0;
}