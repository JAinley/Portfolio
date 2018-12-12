#include "Game_Over.h"
#include "../inc/snake.hpp"

#include <prg_interactive.hpp>

bool Game_Over::onCreate()
{
    return true;
}

bool Game_Over::onDestroy()
{
    return true;
}

void Game_Over::onEntry()
{
    prg::application.addKeyListener(*this);
}

void Game_Over::onExit()
{
    prg::application.removeKeyListener(*this);
}

void Game_Over::onUpdate()
{
}

void Game_Over::onRender(prg::Canvas& canvas)
{
    const std::string text("GAME OVER, PRESS ESC TO EXIT OR U TO RESTART");

  prg::uint text_dims[2];
  prg::Font::MEDIUM.computePrintDimensions(text_dims, text);
  prg::Font::MEDIUM.print(
    canvas,
    prg::application.getScreenWidth() / 2 - text_dims[0] / 2,
    prg::application.getScreenHeight() / 2 - text_dims[1] / 2,
    prg::Colour::RED,
    text);
}
// if user presses u then the game retarts
  //override the onKey() function from prg::IKeyEvent
bool Game_Over::onKey(const prg::IKeyEvent::KeyEvent& key_event)
{
    if(key_event.key_state == KeyEvent::KB_DOWN) {
    switch(key_event.key) {
    case KeyEvent::KB_ESC_KEY:
      prg::application.exit();
      break;
    case 'u':
      prg::application.setState("play_state");
      break;

      }
    }
    return true;
}
