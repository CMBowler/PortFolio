#include"Client.h"
#include "PublicDef.h"

//REMOVE SOON....

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
void Send(int sockfd)// Simple chat program which generates a string and sends it.
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(Csockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int ClientCreate()
{

 memset(&Chints, 0, sizeof Chints);//resets the struct so its not holding any memory.. 
    Chints.ai_family = AF_UNSPEC;//Unknown IP IF ITS V4 OR V6
    Chints.ai_socktype = SOCK_STREAM;//TCP
    Chints.ai_flags = AI_PASSIVE; // use my IP


 if ((rv = getaddrinfo(NULL, PORTC, &Chints, &Cres)) != 0) {// error handling 
        fprintf(stderr, "init CLIENT get addrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

//create a socket from the info found 
if( Csockfd = socket(Cres->ai_family,Cres->ai_socktype,Cres->ai_protocol)!=0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"ERROR Client getting socket: %s\n",gai_strerror(Csockfd));
        return 1;//returning one as error check in main..
   }


if (connect(Csockfd, Cres->ai_addr, Cres->ai_addrlen) == -1) {
            close(Csockfd);
            perror("ERROR client: connect");
			return 1;
}

//TODO: Remove this later just for DEBUGging
inet_ntop(Cres->ai_family, get_in_addr((struct sockaddr *)Cres->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);


	Send(Csockfd);

	// close the socket
	close(Csockfd);
	return 0;
}
