#pragma once

#include "item.h"
#include "../entity/furniture.h"

class FurnitureItem : public Item, 
    public IReferencesUUID<std::shared_ptr<Entity>>
{
public:
  UUID_Field furniture_uuid;
  std::shared_ptr<Furniture> furniture;
  bool placed = false;

  FurnitureItem(Serializer &serializer);
  FurnitureItem(std::shared_ptr<Furniture> furniture);

  std::string getName() const override;
  int getColor() const override;
  int getSprite() const override;
  void renderIcon(Screen &screen, int x, int y) override;
  void renderInventory(Screen &screen, int x, int y) override;
  bool canAttack() override;
  bool interactOn(Tile &tile, Level &level, int xt, int yt, Player &player, int attackDir) override;
  bool isDepleted() override;
  bool matches(const Item &item) override;
  std::shared_ptr<Item> clone() override;

  const UUID_Field &getUUID() const override { return furniture_uuid; }
  void serialize(Serializer &serializer) override;
protected:
  void resolveValueOfUUID(IContainerUUID<std::shared_ptr<Entity>>& contianer) override;
};
