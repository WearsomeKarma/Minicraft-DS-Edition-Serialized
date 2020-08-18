#pragma once

#include "tile.h"
#include "../../item/resource/resource.h"

class OreTile : public Tile
{
public:
  OreTile(int id, const Resource *toDrop);

  void render(Screen &screen, Level &level, int x, int y) override;
  bool mayPass(Level &level, int x, int y, Entity &e) override;
  bool interact(Level &level, int xt, int yt, Player &player, Item &item, int attackDir) override;
  void bumpedInto(Level &level, int x, int y, Entity &entity) override;
  void hurt(Level &level, int x, int y, Mob &source, int dmg, int attackDir) override;

private:
  const Resource *toDrop;
  int color;
  void hurt(Level &level, int x, int y, int dmg);
};
