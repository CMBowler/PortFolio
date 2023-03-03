#ifndef PublicDef_h
#define PublicDef_h
#include <stdio.h>
#include <stdlib.h>
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
#include <sys/select.h>

 int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct sockaddr_in hints;
    struct sockaddr_in their_addr;
    socklen_t addr_size;
// #define PORT "3490"  // the port users will be connecting to
// #define PORTC "3490"
#define _SS_PAD1SIZE 3000
#define BACKLOG 10   // how many pending connections queue will hold
#define MAX 80
#define SA struct sockaddr
/////////server side//

/// @brief CLIENT SIDE/////
int Csockfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct sockaddr_in Chints;// was using the addrinfo but doesnt work for single networking..
    char s[INET6_ADDRSTRLEN];
    int yes =99;
	int rv = 99,rz =99;

char usrname[20];
int PORT;
// #define MAX 80 Defined in server




    


#endif 