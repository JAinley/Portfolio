//
//  MySocketClass.cpp
//  t01
//
//  Created by AINLEY, JOSHUA on 23/11/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#include "MySocketClass.hpp"
#include <iostream>
#include <sstream>
#include <string>



void MySocketClass::Connect()
{
    
    sf::Socket::Status status = socket.connect("152.105.5.134", 11100);
    if(status != sf::Socket::Done)
    {
        //error
    }
}

// send a message via TCP  protocol
void MySocketClass::Send(std::string message)
{
    if(socket.send(message.c_str(), message.length()) != sf::Socket::Done)
    {
        std::cout << "Error" << std::endl;
    }
    else{
            //std::cout << "Sending: " << message << "\n";
    }
}

void MySocketClass::RecieveTCP()
{
    char buffer[50];
    socket.setBlocking(true);
    
    while(true){
        std::memset(buffer, 0, 50);
        std::size_t recieved = 0;
        if(socket.receive(buffer, sizeof(buffer), recieved) != sf::Socket::Done)
        {
            std::cout << "Error receiving" << std::endl;
        }
        else
        {
        std::string s(buffer);
        buffermessage = s;
       
            s = "";
        }
        
    }
}

void MySocketClass::sendUDP(std::string message)
{
    unsigned short port = 10000;
    sf::IpAddress sender = "152.105.5.134";
    
    if(Usocket.send(message.c_str(), message.length() +1, sender, port) != sf::Socket::Done)
    {
        std::cout << "Error sending UDP" << std::endl;
    }
    else{
        //std::cout << "Sending: " << message << "\n";
        message = "";
    }
}

void MySocketClass::RecieveUdp()
{
    char buffer[50];

    Usocket.setBlocking(false);
    while(true)
    {
        unsigned short port = 10000;
        sf::IpAddress sender = "152.105.5.134";
        std::memset(buffer, 0, 50);
        std::size_t recieved = 0;
        if(Usocket.receive(buffer, 50, recieved, sender, port) != sf::Socket::Done)
        {
            
        }
        else{
            std::string s(buffer);
            
            buffermessage = s;
            
        }
    }
}

// allows the wolrd to access the message
std::string MySocketClass::Message()
{
    return buffermessage;
    
}






