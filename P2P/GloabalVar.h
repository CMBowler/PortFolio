#ifndef PublicDef_h
#define PublicDef_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h> // bzero()
#include <netinet/in.h>
#include <unistd.h> // read(), write(), close()
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490"  // the port users will be connecting to
#define _SS_PAD1SIZE 3000
#define BACKLOG 10   // how many pending connections queue will hold
#define MAX 80

int sockfd =99, talkfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct addrinfo hints, *res, *p;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;



// #define MAX 80 Defined in server
#define PORTC "3490"

#define SA struct sockaddr



int Csockfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    int yes =99;
    struct addrinfo Chints, *Cres;
    
    char s[INET6_ADDRSTRLEN];
	int rv = 99;


#endif 