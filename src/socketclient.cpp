
#include "socketclient.h"
#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>
#include<string>
#include<iostream>

socketClient::socketClient()
{
    sock = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        std::cout<<"Socket creation error "<<std::endl; 
        
    } 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
}

void socketClient::ipbin(std::string ip)
{
    if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<=0)  
    { 
        std::cout<<"Invalid address/ Address not supported"<<std::endl;  
        
    } 

}
void socketClient::connecting()
{
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        std::cout<<"Connection Failed "<<std::endl; 
        
    } 
}
void socketClient::sending(char* msg)
{
    send(sock , msg , strlen(msg) , 0 ); 
}
void socketClient::receiving(NetworkChatFrame *networkChatFrame)
{
    while (1){
        while (valread = read( sock , buffer, 1024)>0) {
        wxString botText(buffer, wxConvUTF8);
        networkChatFrame->_mutex.lock();
        networkChatFrame->_panelDialog->AddDialogItem(botText, false,false);}
        networkChatFrame->_mutex.unlock();}
}
   
