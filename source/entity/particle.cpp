#include "particle.h"

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

void Particle::deserialize(Serializer &serializer) 
{
  serializer.loadFromFile_Fields(&time, &duration);
}
