#pragma once

#include "../furniture.h"

class Anvil : public Furniture
{
public:
  Anvil();
  Anvil(Game &game);
  Anvil(Serializer &serializer)
      : Furniture(serializer)
  {}

  bool use(Game &game, Level &level, Player &player, int attackDir) override;
  std::shared_ptr<Furniture> clone(Game &game) override;
};
