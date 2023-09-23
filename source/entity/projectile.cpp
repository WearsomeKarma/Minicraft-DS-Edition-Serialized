#include "projectile.h"
#include "particle.h"

Projectile::Projectile(Serializer &serializer)
: Particle(serializer)
{
  serializer.loadFromFile(&projectileKind);
  owner_refBy_UUID = WeakReference_ByUUID_Entity<Entity>(serializer);
  serializer.loadFromFile_Fields(&xa, &yy);
}

Projectile::Projectile(enum ProjectileKind projectileKind, 
        std::shared_ptr<Entity> owner, double xa, double ya,
        unsigned int duration)
: Particle(PK_PROJECTILE, owner->x, owner->y, duration), 
    projectileKind(projectileKind),
    owner_refBy_UUID(((const Entity&)*owner).getUUID()), 
    xa(xa), ya(ya)
{
  xx = this->x;
  yy = this->y;
  xr = 0;
  yr = 0;
}

void Projectile::tick(Game &game, Level &level, std::shared_ptr<Entity> self)
{
  auto owner = owner_refBy_UUID.get((IContainerUUID<Entity>&)level).lock();

  if (!owner)
  {
    remove();
    return;
  }

  Particle::tick(game, level, self);
  if (removed) return;

  xx += xa;
  yy += ya;
  x = (int)xx;
  y = (int)yy;
}

void Projectile::serialize(Serializer &serializer)
{
  serializer.saveToFile(&projectileKind);
  owner_refBy_UUID.serialize(serializer);
  serializer.saveToFile_Fields(&xa, &yy);
}
