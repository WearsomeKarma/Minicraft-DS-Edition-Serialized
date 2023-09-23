#pragma once

#include "../entitydeserializer.h"

namespace ParticleDeserializer
{
  std::shared_ptr<Entity> deserialize(Serializer &serializer);
};
