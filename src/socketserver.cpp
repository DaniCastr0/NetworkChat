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
       
    //socket descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::attachPort()
{
    
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::receiving()
{
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::accepting(ChatBotFrame *chatBotFrame)
{
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    while (1){
        //cout<<"bucle"<<endl;
        
        while (valread = read( new_socket , buffer, 1024)>0) {
        cout<<"recibo del cliente un mensaje"<<endl;
        wxString botText(buffer, wxConvUTF8);
        chatBotFrame->_panelDialog->AddDialogItem(botText, false,false);}}

    
}
void socketServer::sending(char *msg)
{
    send(new_socket , msg , strlen(msg) , 0 ); 
}
// char *socketServer::reading()
// {
//     valread = read( new_socket , buffer, 1024); 
//     return buffer;
// }
// void socketServer::printing()
// {
//     printf("%s\n",buffer ); 
// }
// int main()
// {
//     socketServer socket;
//     socket.attachPort();
//     socket.receiving();
//     socket.accepting();
//     char *a=socket.reading();
//     //wxString botText(a, wxConvUTF8);
//     cout<<a<<endl;
// }