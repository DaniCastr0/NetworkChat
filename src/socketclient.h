#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "chatgui.h"
#define PORT 8080 

class ChatBotFrame;

class socketClient
{
    int sock;
    int valread;
    struct sockaddr_in serv_addr; 
    char *hello = "Hellofromclient"; 
    char buffer[1024] = {0}; 

    public:
    socketClient();
    void ipbin(std::string ip);
    void connecting();
    void sending(char* msg);
    void receiving(ChatBotFrame *chatBotFrame);
};
#endif