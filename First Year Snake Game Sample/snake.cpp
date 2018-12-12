#include "../inc/snake.hpp"
#include "../inc/collectible.hpp"
#include "../inc/position.hpp"
#include "../inc/play_state.hpp"


void Snake::setScore(int a)
{
    score += a;
}

void AISnake::setAIScore(int a)
{
    AIscore += a;
}

Snake::Snake()
{

}

PlayerSnake::PlayerSnake()
{
    position_.x = 200;
    position_.y = 200;
}

void PlayerSnake::move()
{
    Segment newSegment(position_);
    SegmentList.push_front(newSegment);
    if (growthValue>0)
        growthValue--;
    else
        SegmentList.pop_back();




    switch(direction_){
    case Direction::North:
        position_.y += Speed;
        break;
    case Direction::East:
        position_.x += Speed;
        break;
    case Direction::South:
        position_.y -= Speed;
        break;
    case Direction::West:
        position_.x -= Speed;
        break;

}
    if(position_.x>795 )
    {
        prg::application.setState("game_over");
    }

    if(position_.x<5 )
    {
        prg::application.setState("game_over");
        //changeDirection(Direction::East);
    }

    if(position_.y>595 )
    {
        prg::application.setState("game_over");
    }

    if(position_.y<5 )
    {
        prg::application.setState("game_over");
    }


}

void AISnake::move()
{

    Segment newSegment2(position_);
    SegmentList.push_front(newSegment2);
    if (growthValueAI>0)
        growthValueAI--;
    else
        SegmentList.pop_back();





    switch(direction_){
    case Direction::North:
        position_.y += Speed;
        break;
    case Direction::East:
        position_.x += Speed;
        break;
    case Direction::South:
        position_.y -= Speed;
        break;
    case Direction::West:
        position_.x -= Speed;
        break;

}
    if(position_.x>795 )
    {
        //prg::application.setState("game_over");
        changeDirection(Direction::West);
    }

    if(position_.x<5 )
    {
        changeDirection(Direction::East);
    }

    if(position_.y>595 )
    {
        //prg::application.setState("game_over");
        changeDirection(Direction::South);
    }

    if(position_.y<5 )
    {
        //prg::application.setState("game_over");
        changeDirection(Direction::North);
    }


}

void AISnake::AIchangeDirection()
{
    int randdirec;
    randdirec = rand()%5;
    if(randdirec==0){
    changeDirection(Direction::North);
    }
    if(randdirec==1){
    changeDirection(Direction::East);
    }
    if(randdirec==2){
    changeDirection(Direction::South);
    }
    if(randdirec==3){
    changeDirection(Direction::West);
    }
    if(randdirec==4){
    return;
    }

}


bool Snake::Collision(Snake& other)
{
    float dx, dy, dist, pos1x, pos2x, pos1y, pos2y;
    int radius1 = 10;
    int radius2 = 10;

    pos1x = position_.x;
    pos1y = position_.y;
    pos2x = other.position_.x;
    pos2y = other.position_.y;

    dx= pos1x - pos2x;
    dy = pos1y - pos2y;

    dist = (dx * dx) + (dy * dy);

    if(dist < (radius1 + radius2) * (radius1 +radius2))
    {
        return true;
    }

    return false;
}


bool Snake::Collision(Collectible& other)
{
    float dx, dy, dist, pos1x, pos2x, pos1y, pos2y;
    int radius1 = 10;
    int radius2 = 10;

    pos1x = position_.x;
    pos1y = position_.y;
    pos2x = other.getPosition().x;
    pos2y = other.getPosition().y;

    dx= pos1x - pos2x;
    dy = pos1y - pos2y;

    dist = (dx * dx) + (dy * dy);

    if(dist < (radius1 + radius2) * (radius1 +radius2))
    {
        return true;
    }

    return false;
}

bool Snake::Collision(DropZone& other)
{
    float dx, dy, dist, pos1x, pos2x, pos1y, pos2y;
    int radius1 = 10;
    int radius2 = 10;

    pos1x = position_.x;
    pos1y = position_.y;
    pos2x = other.getPosition().x;
    pos2y = other.getPosition().y;

    dx= pos1x - pos2x;
    dy = pos1y - pos2y;

    dist = (dx * dx) + (dy * dy);

    if(dist < (radius1 + radius2) * (radius1 +radius2))
    {
        return true;
    }

    return false;
}










void Snake::changeDirection(Direction new_direction)
{
    direction_ = new_direction;
}

void Snake::render(prg::Canvas& canvas) const
{
  for(auto p:SegmentList){
  p.render(canvas);
  }
  for(int i=1; i<Radius; i++)
  canvas.drawCircle(
    position_.x,
    position_.y,
    i,
    prg::Colour::BLUE
  );
}

void Snake::setGV(int a)
{
    growthValue++;
}

void AISnake::setAIGV(int a)
{
    growthValueAI++;
}


AISnake::AISnake()
{
    position_.x = 700;
    position_.y = 200;
    //ctor
}

void AISnake::render(prg::Canvas& canvas) const
{
 for(auto p:SegmentList){
  p.render(canvas);
  }
  for(int i=0; i<AIRadius;i++)
  canvas.drawCircle(
    position_.x,
    position_.y,
    i,
    prg::Colour::RED
  );
}



