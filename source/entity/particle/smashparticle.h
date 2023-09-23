#pragma once

#include "../../game.h"
#include "../../gfx/screen.h"
#include "../../level/level.h"
#include "../particle.h"

class SmashParticle : public Particle
{
public:
  SmashParticle(Serializer &serializer) : Particle(serializer) {}
  SmashParticle(int x, int y);

  void render(Screen &screen) override;
};
