#include "particle.h"
#include "entity.h"

Particle::Particle(Serializer &serializer) 
: Entity(EK_PARTICLE)
{
  serializer.loadFromFile_Fields(&time, &duration);
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
  serializer.saveToFile_Fields(&time, &duration);
}
