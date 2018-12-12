#include "../inc/play_state.hpp"
#include <stdio.h>
#include <time.h>
#include "../inc/position.hpp"
#include "../inc/snake.hpp"
#include "Segment.h"


bool PlayState::onCreate()
{
  return true;
}

bool PlayState::onDestroy()
{
  return true;
}

void PlayState::onEntry()
{
  snake_.setPosition(Position(200,200));
  AIsnake_.setPosition(Position(600,200));
  dropzone_[1].setPosition(Position(50,290));
  dropzone_[0].setPosition(Position(750,290));

  snake_.resetScore();
  AIsnake_.resetScore();

  snake_.SegmentList.clear();
  AIsnake_.SegmentList.clear();

  player1Score=0;
  Player2Score=0;;
  prg::application.addKeyListener(*this);
  timer_.start();
  timer2_.start();
  timer3_.start();
}

void PlayState::onExit()
{
  if(player1Score > Player2Score)

  countdown = 90;

  prg::application.removeKeyListener(*this);
}

void PlayState::onUpdate()
{

  //AIsnake_.move();
  for(int i=0; i<5; i++){
    if(snake_.Collision(collectible_[i]))
    {

        collectible_[i].setPosition(Position(rand()% 795, rand()%595));
        snake_.setScore(1);
        snake_.getGV();
        snake_.setGV(1);


    }
    }
    if(snake_.Collision(dropzone_[0]))
    {
    snake_.SegmentList.clear();
    player1Score = snake_.getScore();

    }

    if(snake_.Collision(AIsnake_))
    {
        prg::application.setState("game_over");
    }


    for(int i=0; i<5; i++){
    if(AIsnake_.Collision(collectible_[i]))
    {

        collectible_[i].setPosition(Position(rand()% 750, rand()%550));
        AIsnake_.setAIScore(1);
        AIsnake_.getAIGV();
        AIsnake_.setAIGV(1);


    }
    }
    if(AIsnake_.Collision(dropzone_[1]))
    {
    AIsnake_.SegmentList.clear();
    Player2Score = AIsnake_.getAIScore();

    }

}

void PlayState::onTimer(prg::Timer& timer)
{
    if(timer.getID()==1)
    snake_.move();


    if(timer.getID()==1)
    AIsnake_.move();

    if(timer.getID()==0){
        if(countdown > 0)
        {
            countdown --;
        }

        if(countdown == 0)
        {
            prg::application.setState("game_over");
        }
    }
    if(timer.getID()==2)
    AIsnake_.AIchangeDirection();
}



void PlayState::onRender(prg::Canvas& canvas)
{
  const std::string text2("TIMER " + std::to_string(countdown));
  prg::uint text_dims[2];
  prg::Font::MEDIUM.computePrintDimensions(text_dims, text2);
  prg::Font::MEDIUM.print(canvas, 730 - text_dims[0] /2, 570 - text_dims[1] /2, prg::Colour::MAGENTA, text2);



  const std::string text(std::to_string(Player2Score) + " SNAKE " + std::to_string(player1Score));

  prg::Font::MASSIVE.computePrintDimensions(text_dims, text);
  prg::Font::MASSIVE.print(
    canvas,
    prg::application.getScreenWidth() / 2 - text_dims[0] / 2,
    prg::application.getScreenHeight() / 2 - text_dims[1] / 2,
    prg::Colour::GREY,
    text);
    //x line drawing
    for(int i = 0; i <10; i++){
    canvas.drawLine(0,i,800,i,prg::Colour::GREY);
    };

    for(int i = 600; i > 590; i--){
    canvas.drawLine(0,i,800,i,prg::Colour::GREY);
    };

    //y line drawing
    for(int i = 0; i < 10; i++){
    canvas.drawLine(i,0,i,600,prg::Colour::GREY);
    };

    for(int i = 800; i > 790; i--){
    canvas.drawLine(i,0,i,600,prg::Colour::GREY);
    };



    //goals render
    //red team goal
    for(int i =220; i < 225; i++){
    canvas.drawLine(0,i,50,i,prg::Colour::RED);
    };

    for(int i =360; i < 365; i++){
    canvas.drawLine(0,i,50,i,prg::Colour::RED);
    };

    for(int i =50; i <55; i++){
    canvas.drawLine(i,220,i,364,prg::Colour::RED);
    };

    //blue team goal
    for(int i =220; i < 225; i++){
    canvas.drawLine(800,i,750,i,prg::Colour::BLUE);
    };

    for(int i =360; i < 365; i++){
    canvas.drawLine(800,i,750,i,prg::Colour::BLUE);
    };

    for(int i =745; i <750; i++){
    canvas.drawLine(i,220,i,364,prg::Colour::BLUE);
    };





    // draw a circle where the snake is
for(int i=0; i <2; i++){
  dropzone_[i].render(canvas);
  }
  snake_.render(canvas);
  AIsnake_.render(canvas);
    for(int i=0; i<5; i++){
  collectible_[i].render(canvas);
  }
}


bool PlayState::onKey(const prg::IKeyEvent::KeyEvent& key_event)
{
  if(key_event.key_state == KeyEvent::KB_DOWN) {
    switch(key_event.key) {
    case 'w':
      snake_.changeDirection(Direction::North);
      break;
    case 'd':
      snake_.changeDirection(Direction::East);
      break;
    case 's':
      snake_.changeDirection(Direction::South);
      break;
    case 'a':
      snake_.changeDirection(Direction::West);
      break;
    case KeyEvent::KB_ESC_KEY:
      prg::application.exit();
      break;


    case 'i':
      AIsnake_.changeDirection(Direction::North);
      break;
    case 'j':
      AIsnake_.changeDirection(Direction::West);
      break;
    case 'k':
      AIsnake_.changeDirection(Direction::South);
      break;
    case 'l':
      AIsnake_.changeDirection(Direction::East);
      break;


    //Use this protoype reverse function as a powerUp? in the game as a booby trap




    }
  }
  return true;
}

void PlayState::reset()
{
    PlayerSnake();
    AISnake();

}
