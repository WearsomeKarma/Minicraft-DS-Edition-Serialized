#pragma once

#include "entity.h"

enum ParticleKind
{
  PK_UNSET,
  PK_SMASH,
  PK_TEXT,
  PK_PROJECTILE,
};

class Particle : public Entity
{
  enum ParticleKind particleKind = PK_UNSET;
protected:
  unsigned int time = 0;
  unsigned int duration = 0;

public:

  Particle(Serializer &serializer);
  Particle(enum ParticleKind particleKind) : Entity(EK_PARTICLE), particleKind(particleKind), duration(-1) {}
  Particle(enum ParticleKind particleKind, int x, int y, int duration) : Entity(EK_PARTICLE, x, y), particleKind(particleKind), duration(duration) {}

  virtual ~Particle() {}

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;

  enum ParticleKind getKind() const { return particleKind; }

  void serialize(Serializer &serializer) override;
};
