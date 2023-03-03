#include "Client.h"
#include "Server.h"
#include "PublicDef.h"
#include <pthread.h>
// TODO: make a thread for server run and call variables.
//TODO: Look into Gloabalisation and resetting variables (might be easier to just use sep var names and reuse the struscts)
 
//TODO: Clean up variables and get it to run...
//TODO: Look at cmd line 
//TODO URGENT  make a way of chosing which port number for multiple hosts...
pthread_mutex_t mutex;
int err=0;
void *ServerT(void* a){
   
     if(listen(sockfd,BACKLOG)<0)//-1 = errno
    {
        printf("INIT_Server socket Listening failed...\n");
        return 0;
    }
    printf("Listening...\n");
    //accept time how it works is somewhere will try to call coonect()
    //to the port im listening on..
    // Their connection will be queued waiting to be accepted()
    // you call accept tell it to get the pending connection
    // IT WILL RETURN A NEW SOCKFD FOR THIS CONNECTIONTHE FIRST SOCKFD IS STILL LISTENING FOR NEWCOMERS
    // BUT THE NEW ONE HANDLES SOLELY THE BACK AND FORTH WITH THIS CONN
    
while(1){
    sleep(3);//Sleep for a bit to allow the client to do stuff..a
   
Recieve();//ATM NO NEED TO CALL ANYTHING BECAUSE WE USE GLOBAL VAR RN
// Command exits as connection is finished..
    //TODO simple messaging for DEV Please remove afterusage....
}

    printf("all is well! :))\n");
    return 0;
    

}


int main(int argc, char const *argv[]){


pthread_mutex_init(&mutex,NULL);
static pthread_t Serv;
int fail;
long xy;
 err =Server();
    if(err != 0 ){
        printf("Error on INIT Server see errors:\n");
        return 0;
    } 
    
xy = pthread_create(&Serv,NULL,ServerT,(void *)0);
if(xy){
    printf("@Thread ERROR\n");
    exit(-1);
}
int ch; //TODO STOLEN!!!
printf("\n*****At any point in time press the following:*****\n1.Send message\n0.Quit\n");
    printf("\nEnter choice:");

    do
    {
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            ClientCreate();
            break;
        case 0:
            printf("\nLeaving\n");
            break;
        default:
            printf("\nWrong choice\n");
        }
    } while (ch);
//While that thread is runnign the client will take center stage...

// fail = ClientCreate();
// if(fail != 0 ){
//         printf("Error on Client End see errors:\n");
//     }
// else 
// printf("Ended fairly in love and war :)!\n");

pthread_join(Serv,NULL);

pthread_mutex_destroy(&mutex);
    return 0;

}



//////////////////////////////////////////////////
///SERVER FUNCTIONS/////////////////////////




int Server()
{
    // int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
    // struct sockaddr_in hints;
    // struct sockaddr_storage their_addr;
    // socklen_t addr_size;

    int force =1;
   printf("Enter name:");
    scanf("%s", usrname);

    printf("Enter your port number:");
    scanf("%d", &PORT);
    // struct sigaction sa;
    // int yes=1;
    // int rv1;
 if( (sockfd = socket(AF_INET, SOCK_STREAM ,0))==-1){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"INIT_Server getting socket: %s\n",gai_strerror(sockfd));
        return 1;//returning one as error check in main..
   }
   //Since we will be listening down the line we must bind the socket and the address...
  if (setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FD TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&hints, 0, sizeof hints);//resets the struct so its not holding any memory.. 
    hints.sin_family = AF_INET;//Sets this to IPV4
    // = SOCK_STREAM;//TCP
    hints.sin_port = htons(PORT);//COnverts to big endian format.. Good practice
    hints.sin_addr.s_addr = INADDR_ANY;
   

//SIMPLE VERSION WILL NEED TO BE CHANGED DOWN THE LINE..
  
   if( bind(sockfd, (struct sockaddr *)&hints,sizeof(hints))<0   )//binds to the port we gave it to at the start.
    {
        printf("INIT_Server socket bind failed...\n");
        return 1;
    }
 

return 0;
}




void Recieve()// delete after usage..
{
    
    fd_set active, read;
    addr_size=sizeof(their_addr);
    // Initialize my current set
    FD_ZERO(&active);
    FD_SET(sockfd, &active);
    int k=0;
    int n;
<<<<<<< HEAD
    int f;
    fd_set curr_socks, ready_socks;

    FD_ZERO(&curr_socks);
    FD_SET(connfd, &curr_socks);
    // infinite loop for chat
   int k = 0;
   printf("Entering loop\n");
    while (1)
    {
        k++;
        ready_socks = curr_socks;

        if (select(FD_SETSIZE, &ready_socks, NULL, NULL, NULL) < 0)
=======
            char buff[MAX]={0};

        // TODO FIX THIS THINGY
      while (1)
    {
     
        read = active;

        if (select(FD_SETSIZE, &read, NULL, NULL, NULL) < 0)
>>>>>>> 1ff1c6e34019d3d0fb2d79b6fe6d666e14bdd987
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
<<<<<<< HEAD

        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &ready_socks))
            {

                if (i == connfd)
                {
                    int client_socket;

                    if ((client_socket = accept(connfd, (struct sockaddr *)&their_addr,
=======
//service all the sockets with inputs pending//
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &read))
            {
                        //connection request on orginal socket
                if (i == sockfd)
                {
                    int client_socket;
                    
                    if ((client_socket = accept(sockfd, (struct sockaddr *)&their_addr,
>>>>>>> 1ff1c6e34019d3d0fb2d79b6fe6d666e14bdd987
                                                (socklen_t *)&addr_size)) < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
<<<<<<< HEAD
                    FD_SET(client_socket, &curr_socks);
                }
                else
                {
                    n = recv(i, buff, sizeof(buff), 0);
                    printf("\n%s\n", buff);
                    FD_CLR(i, &curr_socks);
=======
                    FD_SET(client_socket, &active);
                }
                else
                {
                    //data is arriving on an already connected socket
                    n = recv(i, buff, sizeof(buff), 0);
                    printf("\n%s\n", buff);
                    close(i);
                    FD_CLR(i, &active);
>>>>>>> 1ff1c6e34019d3d0fb2d79b6fe6d666e14bdd987
                }
            }
        }

        if (k == (FD_SETSIZE * 2))
            break;
    }
<<<<<<< HEAD
    printf("out of loop :(\n");
=======
    return;
>>>>>>> 1ff1c6e34019d3d0fb2d79b6fe6d666e14bdd987
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////CLIENT FUNCTIONS/////////////////////////
#include"Client.h"
#include "PublicDef.h"

//REMOVE SOON....

// void *get_in_addr(struct sockaddr *sa)
// {
//     if (sa->sa_family == AF_INET) {
//         return &(((struct sockaddr_in*)sa)->sin_addr);
//     }

//     return &(((struct sockaddr_in6*)sa)->sin6_addr);
// }
// void Send(int FUCKfd)// Simple chat program which generates a string and sends it.
// {
	// char buff[MAX];
	// int n;
	// for (;;) {

     
	// 	bzero(buff, sizeof(buff));
	// 	printf("Enter the string : ");
	// 	n = 0;
	// 	while ((buff[n++] = getchar()) != '\n')
	// 		;
	// 	send(FUCKfd, buff, sizeof(buff),0);
	// 	bzero(buff, sizeof(buff));
	// 	if ((strncmp(buff, "exit", 4)) == 0) {
	// 		printf("Client Exit...\n");
	// 		break;
	// 	}
	// }
// }

int ClientCreate()
{


    char buffer[2000] = {0};
    // Fetching port number
    int PORT_server;

    // IN PEER WE TRUST
    printf("Enter the port to send message:"); // Considering each peer will enter different port
    scanf("%d", &PORT_server);

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = {0};
//  memset(&Chints, 0, sizeof Chints);//resets the struct so its not holding any memory.. 
    Chints.sin_family = AF_INET;//Sets this to IPV4
    // = SOCK_STREAM;//TCP
    Chints.sin_port = htons(PORT_server);//COnverts to big endian format.. Good practice
    Chints.sin_addr.s_addr = INADDR_ANY;

 

//create a socket from the info found 
if( (Csockfd = socket(AF_INET,SOCK_STREAM,0))<0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"ERROR Client getting socket: %s\n",gai_strerror(Csockfd));
        return 1;//returning one as error check in main..
   }
int force =1;
 if (setsockopt(Csockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FD TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

if (connect(Csockfd, (struct sockaddr *)&Chints,sizeof Chints) == -1) {
            close(Csockfd);
            perror("ERROR client: connect");
			return 1;
}

//TODO: Remove this later just for DEBUGging
// inet_ntop(Cres->ai_family, get_in_addr((struct sockaddr *)Cres->ai_addr),
//             s, sizeof s);
    printf("client: connecting to %s\n", s);

char buff[MAX];
	int n;
	for (;;) {

     
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		send(Csockfd, buff, sizeof(buff),0);
		bzero(buff, sizeof(buff));
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
	

	// close the socket
	close(Csockfd);
	return 0;
}
