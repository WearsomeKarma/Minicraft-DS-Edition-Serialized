#pragma once

#include <string>
#include "../gfx/color.h"
#include "item.h"
#include "resource/resource.h"

class ResourceItem : public Item
{
public:
  Resource::ID resourceId;
  int count = 1;

  ResourceItem(Serializer &serializer);
  ResourceItem(Resource::ID resourceId);
  ResourceItem(Resource::ID resourceId, int count);

  std::string getName() const override;
  int getColor() const override;
  int getSprite() const override;
  void renderIcon(Screen &screen, int x, int y) override;
  void renderInventory(Screen &screen, int x, int y) override;
  bool interactOn(Tile &tile, Level &level, int xt, int yt, Player &player, int attackDir) override;
  bool isDepleted();
  std::shared_ptr<Item> clone(Game &game) override;

  void serialize(Serializer &serializer) override;
};
