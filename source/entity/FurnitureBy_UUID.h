#pragma once

///
/// Wrapper class for ValueBy_UUID<Entity> to function
/// as ValueBy_UUID<Furniture>
///

#include "../serialization/ValueByUUID.h"
#include "entity.h"
#include "furniture.h"
#include <memory>

class FurnitureBy_UUID : public ValueBy_UUID<std::shared_ptr<Entity>>
{
  std::shared_ptr<Furniture> furniture;
public:
  FurnitureBy_UUID() {}
  FurnitureBy_UUID(Serializer &serializer)
      : ValueBy_UUID<std::shared_ptr<Entity>>(serializer) {}
  FurnitureBy_UUID(FurnitureBy_UUID &furniture);
  FurnitureBy_UUID(std::shared_ptr<Furniture> furniture);

  //TODO: pretty sure u want to make this const cast.
  // const std::shared_ptr<Furniture> unsafeAsFurniture() const
  // { return furniture; }
  std::shared_ptr<Furniture> unsafeAsFurniture() const 
  { return furniture; }

  bool tryGetValue_ByUUID(
          IContainerUUID<std::shared_ptr<Entity>>& container, 
          std::shared_ptr<Entity> &value) override;
  bool trySetActive(
          IContainerUUID<std::shared_ptr<Entity>> &container) override;
};
