
// Client side C/C++ program to demonstrate Socket programming 
#include "socketclient.h"

socketClient::socketClient()
{
    sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        
    } 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
}

void socketClient::ipbin()
{
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        
    } 

}
void socketClient::connecting()
{
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        
    } 
}
void socketClient::sending()
{
    send(sock , hello , strlen(hello) , 0 ); 
}
   
int main(int argc, char const *argv[]) 
{ 
    socketClient socketclient;
    socketclient.ipbin();
    socketclient.connecting();
    socketclient.sending();
    return 0; 
} 
