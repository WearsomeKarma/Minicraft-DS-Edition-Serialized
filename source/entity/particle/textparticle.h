#pragma once

#include "../particle.h"
#include "../../gfx/color.h"
#include "../../gfx/screen.h"

class TextParticle : public Particle
{
private:
  std::string msg;
  int col;

public:
  double xa, ya, za;
  double xx, yy, zz;

  TextParticle(std::string msg, int x, int y, int col);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  void render(Screen &screen) override;
};
