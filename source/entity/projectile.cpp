#include "projectile.h"
#include "particle.h"
#include "../game.h"

Projectile::Projectile(Serializer &serializer)
: Particle(serializer)
{
  serializer.loadFromFile(&projectileKind);
  owner_refBy_UUID = ValueBy_UUID<std::weak_ptr<Entity>>(serializer);
  serializer.loadFromFile_Fields(&xa, &yy);
}

Projectile::Projectile(enum ProjectileKind projectileKind, 
        std::shared_ptr<Entity> owner, double xa, double ya,
        unsigned int duration)
: Particle(PK_PROJECTILE, owner->x, owner->y, duration), 
    projectileKind(projectileKind),
    owner_refBy_UUID(std::weak_ptr<Entity>(owner), owner->getUUID().getID()), 
    xa(xa), ya(ya)
{
  xx = this->x;
  yy = this->y;
  xr = 0;
  yr = 0;
}

void Projectile::initAfterLoad(Game &game)
{
  owner_refBy_UUID.trySetActive(game);
}

void Projectile::tick(Game &game, Level &level, std::shared_ptr<Entity> self)
{
  if (!owner_refBy_UUID.getIsActive())
  {
    remove();
    return;
  }

  auto owner = owner_refBy_UUID.unsafeGet();

  Particle::tick(game, level, self);
  if (removed) return;

  xx += xa;
  yy += ya;
  x = (int)xx;
  y = (int)yy;
}

void Projectile::serialize(Serializer &serializer)
{
  Particle::serialize(serializer);
  serializer.saveToFile(&projectileKind);
  owner_refBy_UUID.serialize(serializer);
  serializer.saveToFile_Fields(&xa, &yy);
}
