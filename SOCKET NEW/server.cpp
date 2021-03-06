  /* Server code in C */
  // Compilar: gcc -o s.exe server.c
 //  Ejecutar: ./s.exe
 
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <chrono>

  //Cambiando a C++
  #include <iostream>
  #include <thread>         // std::thread, std::this_thread::sleep_for
  using namespace std;


  struct sockaddr_in stSockAddr;                
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //Se trabaja con protocolo TCP Handshaking
  char buffer[255];
  int n;
 

  
 
  void aceptClient(int num)
  {
    int ConnectFD = accept(SocketFD, NULL, NULL);
    if(0 > ConnectFD)
      {
        perror("error accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
    do
   {
     //bzero(buffer,256); //Llena de 0 la cadena
       n = read(ConnectFD,buffer,sizeof(buffer));
       if (n < 0) perror("ERROR reading from socket");
       cout<<"Client "<<num<< " replay: "<<buffer<<endl;
       cout<<"Server Write your Message "<<endl;
       
       char integer_string[32];
       sprintf(integer_string, "%d", num);
       strcpy( buffer, "" );
       cin.getline(buffer,sizeof(buffer));
       strcat (buffer,"                   I ve seen your message. Client ");
       strcat(buffer, integer_string); 

       
       n = write(ConnectFD,buffer,sizeof(buffer));
       if (n < 0) perror("ERROR writing to socket");
   
       /* perform read write operations ... */

   }
     while(buffer != "END");
 
      shutdown(ConnectFD, SHUT_RDWR);
 
      close(ConnectFD); //Cierra el Socket ( Socket : puente para que 2 computadoras se comuniquen remota o localmente) CIERRA la comunicación
  }
 
    
  
  int main(void)
  {
    /*
		This function creates a socket and specifies communication style style, 
		which should be one of the socket styles listed in Communication Styles. (TCP en este caso)
		The namespace argument specifies the namespace; it must be PF_LOCAL (see Local Namespace) or PF_INET (see Internet Namespace). 

    */
	
    if(-1 == SocketFD)
    {
      perror("can not create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));	//Separa espcio en memoria para la Estructura
 
    stSockAddr.sin_family = AF_INET;			//Protocolo para la conexión
    stSockAddr.sin_port = htons(1100);			//Puerto para la conexión
    stSockAddr.sin_addr.s_addr = INADDR_ANY;
 
    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("error bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if(-1 == listen(SocketFD, 10)) 
    {
      perror("error listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 

 	//Hace que el Servidor siempre escuche
    for(;;)
    
{      
 
      std::thread t1 (aceptClient,1); 
      std::thread t2 (aceptClient,2); 
      std::thread t3 (aceptClient,3); 
      t1.detach();
      t2.detach();
      t3.detach();/*
      t1.join();
      t2.join();
      t3.join();*/
      std::this_thread::sleep_for(std::chrono::seconds(100));
 
 
   
    //std::thread (aceptClient,ConnectFD);
    //std::thread (aceptClient,ConnectFD).detach();

   // aceptClient(ConnectFD);
    cout<<"Salio"<<endl;
    close(SocketFD);
    return 0;
  }

}
//Referencia: https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Sockets
//g++ client.cpp -o c
//g++ -std=c++11 server.cpp -o s -lpthreadni yo 