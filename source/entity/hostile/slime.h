#pragma once

#include "../mob.h"

class Slime : public Mob
{
public:
  Slime(int lvl);
  Slime(Serializer &serializer)
      : Mob(serializer)
  {}

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  void render(Screen &screen) override;
  void touchedBy(Level &level, Entity &entity) override;

protected:
  void die(Game &game, Level &level) override;
};
