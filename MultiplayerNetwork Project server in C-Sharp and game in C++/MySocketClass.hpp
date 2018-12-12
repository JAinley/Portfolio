//
//  MySocketClass.hpp
//  t01
//
//  Created by AINLEY, JOSHUA on 23/11/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#ifndef MySocketClass_hpp
#define MySocketClass_hpp
#include <SFML/Network.hpp>
#include <stdio.h>


class MySocketClass {
public:
    void Connect();
    void Send(std::string message);
    void RecieveTCP();
    void sendUDP(std::string message);
    void RecieveUdp();
    void UDPConnect();
    std::string Message();
    
private:
    
    sf::TcpSocket socket;
    sf::UdpSocket Usocket;
    sf::IpAddress recipient = "152.105.5.134";
    unsigned short port = 11000;
    unsigned short UDPport = 10000;
    std::string buffermessage;
};

#endif /* MySocketClass_hpp */
