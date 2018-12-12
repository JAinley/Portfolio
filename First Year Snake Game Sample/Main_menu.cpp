#include "Main_menu.h"
#include "../inc/play_state.hpp"
#include <prg_interactive.hpp>
// Main menu state before the players start
bool Main_Menu::onCreate()
{
    return true;
}

bool Main_Menu::onDestroy()
{
    return true;
}

void Main_Menu::onEntry()
{
    prg::application.addKeyListener(*this);
}

void Main_Menu::onExit()
{
    prg::application.removeKeyListener(*this);
}

void Main_Menu::onUpdate()
{
}

void Main_Menu::onRender(prg::Canvas& canvas)
{
    const std::string text("PRESS Y TO START GAME OR ESC TO EXIT");
    prg::uint text_dims[2];
    prg::Font::MEDIUM.computePrintDimensions(text_dims, text);
    prg::Font::MEDIUM.print(
        canvas,
        prg::application.getScreenWidth() / 2 - text_dims[0] / 2,
        prg::application.getScreenHeight() / 2 - text_dims[1] / 2,
        prg::Colour::RED,
        text);
}

//override the onKey() function from prg::IKeyEvent
// when Y is pressed the game is started and if user presses ESC then the game terminates
bool Main_Menu::onKey(const prg::IKeyEvent::KeyEvent& key_event)
{

    if(key_event.key_state == KeyEvent::KB_DOWN)
    {
        switch(key_event.key)
        {
        case KeyEvent::KB_ESC_KEY:
            prg::application.exit();
            break;
        case 'y':
            prg::application.setState("play_state");
            break;

        }
    }
    return true;
}
