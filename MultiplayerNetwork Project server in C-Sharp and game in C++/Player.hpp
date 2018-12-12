//
//  Player.hpp
//  t01
//
//  Created by AINLEY, JOSHUA on 28/09/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MySocketClass.hpp"


class Player {
public:
    void set_speed(float Speed){speed = Speed;}
    void setup(sf::Texture& image, float x, float y, std::string name);
    sf::Sprite carsprite;
    void PlayerUpdate();
    void move();
    void find_target();
    Player();
    Player(Player& p);
    void setName(std::string playername){PlayerName = playername;}
    std::string getName(){return PlayerName;}
    float getPosX(){return posX;}
    float getPosY(){return posY;}
    void setPos(float x, float y, float pangle);
    void setLap(int Plap){lap = Plap;}
    int getLap(){return lap;}
    void setWin(int win){wins += win;}
    int getWins(){return wins;}
    float getRotation(){return angle;}
    

    
private:
    int wins{0};
    int lap{0};
    float radius{10.f};
    float speed{0};
    float angle{0};
    float maxspeed = 5;
    float accel{0.5f};
    float deccel{0.3f};
    float turnspeed{0.05f};
    float slowspeed{1.0f};
    sf::Texture cartex;
    bool hasIntersected;
    bool Checkpoint;
    bool finish;
    sf::IntRect Spriterect;
    sf::IntRect Middlerect;
    sf::IntRect CheckPoint;
    std::string PlayerName;
    float posX;
    float posY;
    sf::CircleShape shape;
    sf::RectangleShape rect;
    sf::IntRect Finish;

};


#endif /* Player_hpp */

