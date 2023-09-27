#pragma once

#include "../utility.h"
#include "../serializer.h"
#include "../../entity/entity.h"

#include <unordered_map>

namespace EntityDeserializer
{
  std::shared_ptr<Entity> deserialize(Serializer &serializer);
};
