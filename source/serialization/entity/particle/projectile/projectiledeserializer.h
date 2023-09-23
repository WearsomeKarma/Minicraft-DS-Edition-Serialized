#pragma once

#include "../../entitydeserializer.h"

class Particle;

namespace ProjectileDeserializer
{
  std::shared_ptr<Particle> deserialize(Serializer &serializer);
}
