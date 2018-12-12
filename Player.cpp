//
//  Player.cpp
//  t01
//
//  Created by AINLEY, JOSHUA on 28/09/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Player::Player(Player& p)
{
    
    
}

Player::Player()
{
    
}

// here is where the player we control is changed
void Player::PlayerUpdate()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if(speed < maxspeed)
        {
            if(speed <= 0)
            {
                speed += deccel;
            }
            else
            {
                speed += accel;
            }
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if(speed > -maxspeed)
        {
            if(speed >= 0)
            {
                speed -= deccel;
            }
            else
            {
                speed -= accel;
            }
        }
    }
    
    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
    {
        if (speed - deccel >= 0)
        {
            speed -= deccel;
        }
        else if (speed + deccel <= 0)
        {
            speed += deccel;
        }
        else speed = 0;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if(speed !=0)
        {
            angle = angle - turnspeed * speed / maxspeed;
           
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if(speed !=0)
        {
            angle = angle + turnspeed * speed / maxspeed;
            
        }
    }

    // when the player enters the middle zone it slows them down so cheating isnt worth it
    if(Spriterect.intersects(Middlerect))
    {
        if(speed > 3)
        {
            speed = 0;
            accel = 0.2f;
            maxspeed = 3;
        }
    }
    else
    {
        accel = 0.5f;
        maxspeed = 5;
    }
    
    // sees if the player has gone through the checkpoint
    if(Spriterect.intersects(CheckPoint) && !Checkpoint)
    {
        Checkpoint = true;
        std::cout << "Checkpoint" << std::endl;
    }
    
    // if the player has gone through the checkpoint and finish line then a lap is awarded
    if(Spriterect.intersects(Finish) && Checkpoint == true)
    {
        lap +=1;
        Checkpoint = false;
        std::cout << " Lap complete" << std::endl;
    }

    // sets the roattion of the sprite and the rectangle around the sprite for collision
    posX += (sin(angle) * speed);
    posY -= (cos(angle) * speed);
    carsprite.setPosition(posX, posY);
    float rotation = angle * 180/3.14;
    carsprite.setRotation(rotation);
    Spriterect = sf::IntRect{(int)posX, (int)posY, 8, 10};

}

// this function is for when we receive the players positions from the server
void Player::setPos(float x, float y, float pangle)
{
    posX = x;
    posY = y;
    angle = pangle;
    carsprite.setRotation(angle * 180/3.14);
    carsprite.setPosition(x, y);
    
}

// the inital setup for all the starter values 
void Player::setup(sf::Texture& image, float x, float y, std::string name)
{
    posX = x;
    posY = y;
    cartex = image;
    carsprite.setTexture(cartex);
    carsprite.setPosition(posX, posY);
    carsprite.setOrigin(8, 15);
    setName(name);
    Middlerect = sf::IntRect{160, 130, 660, 450};
    CheckPoint = sf::IntRect{825, 257, 960, 425};
    Finish = sf::IntRect{12, 350, 142, 274};
}


