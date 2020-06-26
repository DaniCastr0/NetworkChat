#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

class socketClient
{
    int sock;
    int valread;
    struct sockaddr_in serv_addr; 
    char *hello = "Hellofromclient"; 
    char buffer[1024] = {0}; 

    public:
    socketClient();
    void ipbin();
    void connecting();
    void sending();
};