#include "../inc/collectible.hpp"

void Collectible::render(prg::Canvas& canvas) const
{

for(int i = 1; i <ColRadius; i++){
  canvas.drawCircle(
    position_.x,
    position_.y,
    i,
    prg::Colour::GREEN
    );

  }
}


