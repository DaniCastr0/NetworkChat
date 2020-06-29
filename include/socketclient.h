#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "chatgui.h"
#define PORT 8080 

//based on tutorial on https://www.geeksforgeeks.org/socket-programming-cc/

class NetworkChatFrame;

class socketClient
{
    int sock;
    int valread;
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 

    public:
    socketClient();
    void ipbin(std::string ip);
    void connecting();
    void sending(char* msg);
    void receiving(NetworkChatFrame *networkChatFrame);
};
#endif