#pragma once

#include "../furniture.h"

class Furnace : public Furniture
{
public:
  Furnace();
  Furnace(Serializer &serializer)
      : Furniture(serializer)
  {}

  bool use(Game &game, Level &level, Player &player, int attackDir) override;
  std::shared_ptr<Furniture> clone() override;
};
