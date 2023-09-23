#pragma once

#include "../entitydeserializer.h"

namespace FurnitureDeserializer
{
  std::shared_ptr<Entity> deserialize(Serializer &serializer);
};
