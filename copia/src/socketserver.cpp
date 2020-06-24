#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "socketserver.h" 
#include <string> 
#include<iostream>
#define PORT 8080 

socketServer::socketServer()
{
    opt=1;
    addrlen = sizeof(address); 
     
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
}
void socketServer::attachPort()
{
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
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
void socketServer::accepting()
{
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
}
char socketServer::reading()
{
    valread = read( new_socket , buffer, 1024); 
    return valread;
}
void socketServer::printing()
{
    printf("%s\n",buffer ); 
}
int main(int argc, char const *argv[]) 
{ 
    socketServer socketserver;
    socketserver.attachPort();
    socketserver.receiving();
    socketserver.accepting();
    char a=socketserver.reading();
    socketserver.printing();
    return 0; 
} 
