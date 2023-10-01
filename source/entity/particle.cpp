#include "particle.h"
#include "entity.h"

Particle::Particle(Serializer &serializer) 
: Entity(serializer)
{
  serializer.loadFromFile(&particleKind);
  serializer.loadFromFile(&time);
  serializer.loadFromFile(&duration);
}

void Particle::tick(Game &game, Level &level, std::shared_ptr<Entity> self)
{
  time++;
  if (time > duration)
  {
    remove();
  }
}

void Particle::serialize(Serializer &serializer) 
{
  Entity::serialize(serializer);
  serializer.saveToFile(&particleKind);
  serializer.saveToFile(&time);
  serializer.saveToFile(&duration);
}
