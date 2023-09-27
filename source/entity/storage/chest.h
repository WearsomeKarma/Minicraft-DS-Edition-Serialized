#pragma once

#include "../furniture.h"
#include "../../item/inventory.h"

class Chest : public Furniture
{
private:
  std::shared_ptr<Inventory> inventory;

public:
  Chest();
  Chest(Serializer &serializer);

  bool use(Game &game, Level &level, Player &player, int attackDir) override;
  std::shared_ptr<Furniture> clone() override;

  bool hasInventory() override { return true; }
  std::shared_ptr<Inventory> getInventory() override { return inventory; }

  void serialize(Serializer &serializer) override;
};
