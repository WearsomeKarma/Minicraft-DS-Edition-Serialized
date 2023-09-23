#include "projectiledeserializer.h"

#include "../../../../entity/projectile.h"
#include "../../../../entity/projectile/spark.h"

std::shared_ptr<Particle> ProjectileDeserializer::deserialize(
        Serializer &serializer)
{
  BEGIN_DESERIALIZATION(serializer, Projectile)
      CASE_DESERIALIZE__WITH(PjK_UNKNONW, nullptr)
      CASE_DESERIALIZE__AS(PjK_SPARK, serializer, Spark, Projectile)
  END_DESERIALIZATION__AS(Particle)
}
