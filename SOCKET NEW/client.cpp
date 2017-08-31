 /* Client code in C */
 
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
 
  //Cambiando a C++
  #include <iostream>
  using namespace std;

  int main(void)
  {
    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int n;
	char buffer[255];
 
    if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(1100);
    Res = inet_pton(AF_INET, "192.168.1.2", &stSockAddr.sin_addr);
 
    if (0 > Res)
    {
      perror("error: first parameter is not a valid address family");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
      perror("char string (second parameter does not contain valid ipaddress");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    do
    {
    	cout<<"Client Write your Message "<<endl;
    	cin.getline(buffer,sizeof(buffer));
    	n = write(SocketFD,buffer,sizeof(buffer));
    	/* perform read write operations ... */

		//bzero(buffer,256);
	    n = read(SocketFD,buffer,sizeof(buffer));
	    if (n < 0) perror("ERROR reading from socket");
	    cout<<"Server replay: "<<buffer<<endl;
	    //printf("Server replay: [%s]\n",buffer);

    }
    while(buffer != "END");
    
     
 
    shutdown(SocketFD, SHUT_RDWR);
 
 
    close(SocketFD);
    return 0;
  }

//Referencia: https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Sockets
