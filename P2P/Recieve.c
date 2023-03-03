#include "PublicDef.h"


int main()
{
    int force =1;
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

  if(listen(sockfd,BACKLOG)<0)//-1 = errno
    {
        printf("INIT_Server socket Listening failed...\n");
        return 0;
    }
    printf("Listening...\n");

    fd_set active, read;
    addr_size=sizeof(their_addr);
    // Initialize my current set
    FD_ZERO(&active);
    FD_SET(sockfd, &active);
    int k=0;
    int n;
            char buff[MAX]={0};

        // TODO FIX THIS THINGY
      while (1)
    {
     
        read = active;

        if (select(FD_SETSIZE, &read, NULL, NULL, NULL) < 0)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
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
                                                (socklen_t *)&addr_size)) < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    FD_SET(client_socket, &active);
                }
                else
                {
                    //data is arriving on an already connected socket
                    n = recv(i, buff, sizeof(buff), 0);
                    printf("\n%s\n", buff);
                    close(i);
                    FD_CLR(i, &active);
                }
            }
        }

        if (k == (FD_SETSIZE * 2))
            break;
    }

   return 0;
}



//     while(1){
//     int Sconfd,i;
// 	int ret=0;
	
//     addr_size = sizeof(their_addr);
//     if(talkfd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&addr_size)<0){//errno -1 for socket err will cal that variable gloabaly
//       printf("INIT_Server Accept failed...\n");
//         continue;
//     }
//     printf("Connected to a client\n");
    
//         char buff[MAX]={0};
//  printf("in loop\n");
// int n=0;
// int len;
//  len = strlen(buff);
//          bzero(buff, MAX);
//         // read the message from client and copy it in buffer

//           FD_SET(talkfd, &current_sockets);

//       if((n= recv(talkfd, (void*)buff, len, 0))==-1){
//         printf("ERROR HERE in RECIEVING THE FUCKING FILE\n");\
//       }

//         // print buffer which contains the client contents
//         printf("From client: %s\t\n", buff);
      
//    }   



// close(talkfd);// Command exits as connection is finished..
//     //TODO simple messaging for DEV Please remove afterusage....

// return 0;
// }