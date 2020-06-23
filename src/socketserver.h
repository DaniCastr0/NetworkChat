#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string> 
#define PORT 8080 

class socketServer{
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt; 
    char buffer[1024]; 
    int addrlen;

    public:
    socketServer();
    void attachPort();
    void receiving();
    void accepting();
    char reading();
    void printing();
    
};