//
//  MainMenu.cpp
//  t01
//
//  Created by AINLEY, JOSHUA on 07/12/2017.
//  Copyright © 2017 Cordry, Julien. All rights reserved.
//

#include "MainMenu.hpp"


mainMenu::mainMenu()
{
    menu.loadFromFile("Menu.png");
    menuBackground.setTexture(menu);
}

void mainMenu::MenuUpdate()
{
    std::string playername;
    sf::RenderWindow window(sf::VideoMode(980, 720), "SFML works!");
    window.setFramerateLimit(90);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        menuBackground.setPosition(0,0);
        window.draw(menuBackground);
        
        // get the user to enter their name for their player name and move to the game loop
        window.display();
        std::cout << "Enter player name!" << std::endl;
        std::cin >> playername;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            window.close();
            World world(playername);
            world.WorldUpdate();
        }
    }
    
}
