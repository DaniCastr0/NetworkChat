
// Client side C/C++ program to demonstrate Socket programming 
#include "socketclient.h"
#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>
#include<string>

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

void socketClient::ipbin(std::string ip)
{
    if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0)  
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
void socketClient::sending(char* msg)
{
    send(sock , msg , strlen(msg) , 0 ); 
}
void socketClient::receiving(NetworkChatFrame *networkChatFrame)
{
    while (1){
        //cout<<"bucle"<<endl;
        while (valread = read( sock , buffer, 1024)>0) {
        wxString botText(buffer, wxConvUTF8);
        networkChatFrame->_panelDialog->AddDialogItem(botText, false,false);}}
}
   
