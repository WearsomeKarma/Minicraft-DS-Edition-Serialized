#pragma once

#include "../gfx/color.h"
#include "../gfx/screen.h"
#include "../item/item.h"
#include "../sound/sound.h"
#include "../level/level.h"
#include "entity.h"

class ItemEntity : public Entity
{
private:
  int lifeTime;
  int time = 0;

protected:
  int walkDist = 0;
  int dir = 0;
  int xKnockback, yKnockback;
  void touchedBy(Level &level, Entity &entity) override;

public:
  int hurtTime = 0;
  double xa, ya, za;
  double xx, yy, zz;
  std::shared_ptr<Inventory> inventory;

  ItemEntity(Serializer &serializer);
  ItemEntity(std::shared_ptr<Item> item, int x, int y);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  bool isBlockableBy(Mob &mob) override;
  void render(Screen &screen) override;
  void take(Player &player);

  bool hasInventory() override { return true; }
  std::shared_ptr<Inventory> getInventory() override { return inventory; }

  void serialize(Serializer &serializer) override;
};
