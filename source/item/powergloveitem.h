#pragma once

#include "item.h"
#include "../serialization/serializer.h"

class PowerGloveItem : public Item
{
public:
  PowerGloveItem() : Item(IK_POWERGLOVE) {}
  PowerGloveItem(Serializer &serializer)
      : Item(serializer)
  {}

  std::string getName() const override;
  int getColor() const override;
  int getSprite() const override;
  void renderIcon(Screen &screen, int x, int y) override;
  void renderInventory(Screen &screen, int x, int y) override;
  bool interact(Player &player, Entity &entity, int attackDir) override;
  std::shared_ptr<Item> clone() override;
};
