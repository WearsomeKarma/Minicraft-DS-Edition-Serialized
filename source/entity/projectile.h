#pragma once

#include "entity.h"
#include "particle.h"

#include "../serialization/ValueByUUID.h"

enum ProjectileKind
{
  PjK_UNKNONW = 0,
  PjK_SPARK,
};

class Projectile : public Particle
{
  enum ProjectileKind projectileKind;
protected:
  ValueBy_UUID<std::weak_ptr<Entity>> owner_refBy_UUID;
public:
  double xa, ya;
  double xx, yy;

  Projectile(Serializer &serializer);
  Projectile(enum ProjectileKind projectileKind) 
      : Particle(PK_PROJECTILE), projectileKind(projectileKind) {}
  Projectile(enum ProjectileKind projectileKind, std::shared_ptr<Entity> owner, 
          double xa, double ya, unsigned int duration);

  virtual ~Projectile() {}

  void initAfterLoad(Game &game) override;
  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;

  enum ProjectileKind getKind() {return projectileKind; }

  void serialize(Serializer &serializer) override;
};
