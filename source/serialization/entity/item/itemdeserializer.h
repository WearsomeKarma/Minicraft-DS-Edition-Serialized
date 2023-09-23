#pragma once

#include "../entitydeserializer.h"

namespace ItemEntityDeserializer
{
  std::shared_ptr<Entity> deserialize(Serializer &serializer);
}
