//
//  MainMenu.hpp
//  t01
//
//  Created by AINLEY, JOSHUA on 07/12/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <SFML/Network.hpp>
#include "MySocketClass.hpp"
#include "World.hpp"

class mainMenu{
public:
    mainMenu();
    void MenuUpdate();
     
private:
    sf::Texture menu;
    sf::Sprite menuBackground;
};

#endif /* MainMenu_hpp */
