#pragma once

#include "entity.h"

class Particle : public Entity
{
protected:
  unsigned int time = 0;
  unsigned int duration = 0;

public:
  Particle(std::shared_ptr<UUID> uuid) : Entity(uuid) {}
  Particle(std::shared_ptr<UUID> uuid, int x, int y);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  void render(Screen &screen) override;

  void serialize(Serializer &serializer) override;
  void deserialize(Serializer &serializer) override;
};
