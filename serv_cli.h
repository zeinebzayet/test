#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#define PORT 8080
#define NMAX 10

/* Structure d'une question */
struct question
{
int pidc;  /* pid du client */
int quest; /* question du client */
};


/* Structure d'une réponse */
struct reponse
{
int pidserveur; /* pid du serveur */
int rep[NMAX]; /* reponse du seveur */
};