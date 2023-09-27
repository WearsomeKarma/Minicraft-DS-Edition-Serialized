#pragma once

#include "../utility.h"
#include "../../item/item.h"

namespace ItemDeserializer
{
  std::shared_ptr<Item> deserialize(Serializer &serialize);
}
