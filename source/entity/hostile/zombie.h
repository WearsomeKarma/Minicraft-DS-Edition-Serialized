#pragma once

#include "../mob.h"

class Zombie : public Mob
{
public:
  Zombie(int lvl);
  Zombie(Serializer &serializer)
      : Mob(serializer)
  {}

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  void render(Screen &screen) override;
  void touchedBy(Level &level, Entity &entity);

protected:
  void die(Game &game, Level &level);
};
