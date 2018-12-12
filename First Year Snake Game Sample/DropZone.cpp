#include "DropZone.h"


DropZone::DropZone()
{
    //ctor
}

void DropZone::render(prg::Canvas& canvas) const
{
for(int i=15; i<20;i++)
  canvas.drawCircle(
    position_.x,
    position_.y,
    i,
    prg::Colour::BLUE
    );

}


