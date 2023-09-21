#pragma once

#include "../../game.h"
#include "../../gfx/screen.h"
#include "../../level/level.h"
#include "../particle.h"

class SmashParticle : public Particle
{
public:
  SmashParticle(int x, int y);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  void render(Screen &screen) override;
};
