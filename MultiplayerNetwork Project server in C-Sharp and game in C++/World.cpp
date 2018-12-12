//
//  World.cpp
//  t01
//
//  Created by AINLEY, JOSHUA on 07/12/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#include "World.hpp"
#include <iostream>
#include <sstream>
#include <string>

// load the wolrd and create the player we control and send the player details to the server
World::World(std::string name)
{
    track.loadFromFile("Track.png");
    track.setSmooth(true);
    car.loadFromFile("car2.png");
    font.loadFromFile("Funny & Cute.ttf");
    text.setFont(font);
    lapText.setFont(font);
    Background.setTexture(track);

    currentPlayer->setup(car, 45, 379, name);
    players.push_back(currentPlayer);
    
    mySocket.Connect();
    mySocket.Send("ADD:" + currentPlayer->getName() + ":");

}

// adds more players to the vector but if they exist dont add them
void World::AddPlayer(std::string name)
{
    bool playerexists = false;
    for(auto* p : players)
    {
        if(p->getName() == name)
        {
            playerexists = true;
        }
    }
    
    if(!playerexists)
    {
        Player* player = new Player();
        player->setup(car, 80, 401, name);
        players.push_back(player);
        std::cout << "player added: " + name << std::endl;
    }
}

// updates the positions for the other players in the vector
void World::UpdatePlayerPositions(std::string name, float posx, float posy, int lap, float angle)
{
    for(auto* p : players)
    {
        if(p->getName() != name)
        {
            AddPlayer(name);
        }
        if(p->getName() == name)
        {
            p->setPos(posx, posy, angle);
            p->setLap(lap);

        }
    }
}

// splis the message and decides what to do with them depending on the message contents
void World::SplitString(std::string s)
{
        std::istringstream ss(s);
        std::string token;
        char delim = ':';
        std::vector<std::string> messageInfo;
        while(std::getline (ss, token, delim)){
            messageInfo.push_back(token);
 
        }

    if(messageInfo[0] == "ADD")
    {
        AddPlayer(messageInfo[1]);
    }
    if(messageInfo[1] == "MOVE")
    {
        UpdatePlayerPositions(messageInfo[0], std::stof(messageInfo[2]), std::stof(messageInfo[3]), std::stoi(messageInfo[4]), std::stof(messageInfo[5]));
    }
    if(messageInfo[0] == "WIN")
    {
        WhoWon = messageInfo[1];
    }
    
}

// reset after someone completes three laps
void World::reset()
{
    currentPlayer->setLap(0);
    currentPlayer->setPos(80, 401, 0);
    currentPlayer->set_speed(0);
    //currentPlayer->setAngle(0);
    won = false;
}

void World::WorldUpdate()
{
    sf::RenderWindow window(sf::VideoMode(980, 720), "SFML works!");
    window.setFramerateLimit(90);
    
    // create the receive threads
    sf::Thread UDPThread(&MySocketClass::RecieveUdp, &mySocket);
    UDPThread.launch();
    sf::Thread TCPThread(&MySocketClass::RecieveTCP, &mySocket);
    TCPThread.launch();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //get the message from te thread then pass it to the string splitter and then make the message null
        ServerMessage = mySocket.Message();
        SplitString(ServerMessage);
        ServerMessage = "";
    
        // update the current player(the one we control) and send via udp the psotions and name and lap and rotation
        currentPlayer->PlayerUpdate();
        mySocket.sendUDP(currentPlayer->getName() + ":" + "MOVE:" + std::to_string(currentPlayer->getPosX()) + ":" + std::to_string(currentPlayer->getPosY()) + ":" + std::to_string(currentPlayer->getLap()) + ":" + std::to_string(currentPlayer->getRotation()));
        
        window.clear();
        Background.setPosition(0, 0);
        window.draw(Background);
        
        // checks for the win conditions and changes the text
        for(auto* p : players)
        {
            if(p->getLap() == 3 && !won)
            {
                won = true;
                std::cout << p->getName() + "CONGRATS U WON!!!!!!!" << std::endl;
                text.setCharacterSize(30);
                text.setString(p->getName() + " YOU WON!");
                p->setWin(1);
                mySocket.Send("WIN:" + p->getName() + ":" + std::to_string(p->getWins()) + ":");
                reset();
            }
            window.draw(p->carsprite);
        }
        lapText.setCharacterSize(30);
        lapText.setPosition(500, 360);
        lapText.setString("Lap: " + std::to_string(currentPlayer->getLap()) + "/3" );

        window.draw(lapText);
        window.draw(text);
        window.display();
        
    }
    

}
