#pragma once

#include "../entitydeserializer.h"

namespace MobDeserializer
{
  std::shared_ptr<Entity> deserialize(Serializer& serializer);
};
