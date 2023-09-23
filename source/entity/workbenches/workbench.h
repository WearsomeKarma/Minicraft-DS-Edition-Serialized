#pragma once

#include "../furniture.h"
#include "../../item/crafting/recipe.h"

class Workbench : public Furniture
{
public:
  Workbench();
  Workbench(Serializer &serializer)
      : Furniture(serializer)
  {}

  bool use(Game &game, Level &level, Player &player, int attackDir) override;
  std::shared_ptr<Furniture> clone() override;
};
