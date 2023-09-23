#include "itemdeserializer.h"
#include "../../../entity/itementity.h"
#include <memory>

std::shared_ptr<Entity> ItemEntityDeserializer::deserialize(
        Serializer &serializer)
{
  auto itemEntity = std::make_shared<ItemEntity>(serializer);
  return std::static_pointer_cast<Entity>(itemEntity);
}
