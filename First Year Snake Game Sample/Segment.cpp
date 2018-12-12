#include "Segment.h"
#include "../inc/position.hpp"

Segment::Segment(Position p) : position_(p)
{

    //ctor
}


//renders the segment parts and colours in the circle
void Segment::render(prg::Canvas& canvas) const
{
    for(int i=1; i<10; i++)
        canvas.drawCircle(
        position_.x,
        position_.y,
        i,
        prg::Colour::GREEN
    );
}


