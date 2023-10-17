#include "lantern.h"

Lantern::Lantern()
    : Furniture(FK_LANTERN, "Lantern")
{
  col = Color::get(-1, 000, 111, 555);
  sprite = 5;
  xr = 3;
  yr = 2;
}

Lantern::Lantern(Game &game)
    : Lantern()
{
  game.assignUUID(*this);
}

int Lantern::getLightRadius()
{
  return 12;
}

std::shared_ptr<Furniture> Lantern::clone(Game &game)
{
  return std::make_shared<Lantern>(game);
}
