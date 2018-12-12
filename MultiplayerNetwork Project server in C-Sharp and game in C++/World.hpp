//
//  World.hpp
//  t01
//
//  Created by AINLEY, JOSHUA on 07/12/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <SFML/Network.hpp>
#include "MySocketClass.hpp"

class World{
public:
    World(std::string name);
    std::vector<Player*> players;
    void AddPlayer(std::string name);
    void WorldUpdate();
    void SplitString(std::string s);
    MySocketClass mySocket;
    void UpdatePlayerPositions(std::string name, float posx, float posy, int lap, float angle);
    void reset();
    
private:
    sf::Texture track, car;
    sf::Font font;
    sf::Text text;
    sf::Text lapText;
    sf::Sprite Background;
    Player* currentPlayer = new Player();
    std::string ServerMessage;
    bool won;
    std::string WhoWon;

};
#endif /* World_hpp */
