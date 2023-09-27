#include "particledeserializer.h"

#include "../../../entity/particle.h"
#include "../../../entity/particle/smashparticle.h"
#include "../../../entity/particle/textparticle.h"

#include "projectile/projectiledeserializer.h"

std::shared_ptr<Entity> ParticleDeserializer::deserialize(Serializer &serializer)
{
  BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, Particle)
      CASE_DESERIALIZE__AS(PK_SMASH, serializer, SmashParticle, Particle)
      CASE_DESERIALIZE__AS(PK_TEXT, serializer, TextParticle, Particle)
      CASE_DESERIALIZE__WITH(PK_PROJECTILE, 
              ProjectileDeserializer::deserialize(serializer))
  END_DESERIALIZATION__AS(Entity)
}
