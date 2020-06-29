#ifndef SERVER_H_
#define SERVER_H_

#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <string> 
#include "chatgui.h"

#define PORT 8080 

class NetworkChatFrame;

class socketServer{
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt; 
    char buffer[1024]={0}; 
    int addrlen;
    

    public:
    socketServer();
    void attachPort();
    void receiving();
    void accepting(NetworkChatFrame *networkChatFrame);
    void sending(char* msg);
    
    
};
#endif