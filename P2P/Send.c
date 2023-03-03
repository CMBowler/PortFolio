#include "PublicDef.h"
#include <stdio.h>

int main(){


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




unsigned long ha =(MAX);

    	int n;
        char buffer[2000] = {0};
        char X[1024] = {0};

<<<<<<< HEAD
     
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
        getline(&buff,&ha,stdin);
		n = 0;
		while ((buff[n++] = getchar()) != '\n');
        buff[n+1] = '\0';
        send(Csockfd, buff[MAX], 13, 0);
        bzero(buff, sizeof(buff));
	
	
=======
	// 	char* name =(char*)malloc(sizeof(20));
    // 	printf("Enter the string : \n");
     char dummy;
    printf("Enter your message:");
    scanf("%c", &dummy); // a single newline character is kept from when the port number was read
    // need newline character to be discarded

    // scanf("%[^\n]s", hello); // newline character is the delimiter. That means we stop at newline.
    //  I know fgets, so I replaced it
    fgets(X, 1024, stdin);
    process_buffer(X, 1024);
    sprintf(buffer, "[PORT:%d] says: %s", PORT, X); // format of data sent
    // this gets sent to the buffer

    send(Csockfd, buffer, sizeof(buffer), 0); // send to the created socket
    printf("\nMessage sent\n");
    close(sock); // then immediately close
>>>>>>> 1ff1c6e34019d3d0fb2d79b6fe6d666e14bdd987
	

	// close the socket
	close(Csockfd);



 return 0;   
}


//  char dummy;
//     printf("Enter your message:");
//     scanf("%c", &dummy); // a single newline character is kept from when the port number was read
//     // need newline character to be discarded

//     // scanf("%[^\n]s", hello); // newline character is the delimiter. That means we stop at newline.
//     //  I know fgets, so I replaced it
//     fgets(hello, 1024, stdin);
//     process_buffer(hello, 1024);
//     sprintf(buffer, "%s[PORT:%d] says: %s", name, PORT, hello); // format of data sent
//     // this gets sent to the buffer

//     send(sock, buffer, sizeof(buffer), 0); // send to the created socket
//     printf("\nMessage sent\n");
//     close(sock); // then immediately close