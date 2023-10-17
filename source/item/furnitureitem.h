#pragma once

#include "item.h"
#include "../entity/furniture.h"
#include "../entity/FurnitureBy_UUID.h"

class FurnitureItem : public Item
{
public:
  FurnitureBy_UUID furniture;
  bool placed = false;

  FurnitureItem(Serializer &serializer);
  FurnitureItem(std::shared_ptr<Furniture> furniture);

  void initAfterLoad(Game &game) override;
  std::string getName() const override;
  int getColor() const override;
  int getSprite() const override;
  void renderIcon(Screen &screen, int x, int y) override;
  void renderInventory(Screen &screen, int x, int y) override;
  bool canAttack() override;
  bool interactOn(Tile &tile, Level &level, int xt, int yt, Player &player, int attackDir) override;
  bool isDepleted() override;
  bool matches(const Item &item) override;
  std::shared_ptr<Item> clone(Game &game) override;

  void serialize(Serializer &serializer) override;
};
