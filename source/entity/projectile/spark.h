#pragma once

#include <memory>
#include "../projectile.h"

class Spark : public Projectile 
{
public:

  Spark(Serializer &serializer)
      : Projectile(serializer)
  {}
  Spark(std::shared_ptr<Entity> owner, double xa, double ya);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  void render(Screen &screen) override;
  bool isBlockableBy(Mob &mob) override;
};
