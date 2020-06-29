#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "socketserver.h" 
#include <string> 
#include<iostream>
#include<memory>
#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>

using namespace std;

#define PORT 8080 

socketServer::socketServer()
{
    opt=1;
    addrlen = sizeof(address); 

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::attachPort()
{
    
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::receiving()
{
    if (listen(server_fd, 3) < 0) 
    { 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::accepting(NetworkChatFrame *networkChatFrame)
{
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) 
    { 
        exit(EXIT_FAILURE); 
    } 
    while (1){
        
        while (valread = read( new_socket , buffer, 1024)>0) {
        wxString botText(buffer, wxConvUTF8);
        networkChatFrame->_mutex.lock();
        networkChatFrame->_panelDialog->AddDialogItem(botText, false,false);
        networkChatFrame->_mutex.unlock();}}

    
}
void socketServer::sending(char* msg)
{
    send(new_socket , msg, strlen(msg) , 0 ); 
}
