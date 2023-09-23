#pragma once

#include "../furniture.h"

class Oven : public Furniture
{
public:
  Oven();
  Oven(Serializer &serializer)
      : Furniture(serializer)
  {}

  bool use(Game &game, Level &level, Player &player, int attackDir) override;
  std::shared_ptr<Furniture> clone() override;
};
