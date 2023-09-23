#pragma once

#include "entity.h"
#include "EntityReferenceByUUID.h"
#include "particle.h"

enum ProjectileKind
{
  PjK_UNKNONW = 0,
  PjK_SPARK,
};

class Projectile : public Particle
{
  enum ProjectileKind projectileKind;
protected:
  WeakReference_ByUUID_Entity<Entity> owner_refBy_UUID;
public:
  double xa, ya;
  double xx, yy;

  // USED FOR DESERIALIZATION!!! DO NOT USE!!!
  Projectile() {}
  // -----------------------------------------

  Projectile(Serializer &serializer);
  Projectile(enum ProjectileKind projectileKind) 
      : Particle(PK_PROJECTILE), projectileKind(projectileKind) {}
  Projectile(enum ProjectileKind projectileKind, std::shared_ptr<Entity> owner, 
          double xa, double ya, unsigned int duration);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;

  enum ProjectileKind getKind() {return projectileKind; }

  void serialize(Serializer &serializer) override;
};
