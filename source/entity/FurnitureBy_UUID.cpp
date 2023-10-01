#include "FurnitureBy_UUID.h"
#include <memory>

FurnitureBy_UUID::FurnitureBy_UUID(FurnitureBy_UUID &furniture) 
    : ValueBy_UUID<std::shared_ptr<Entity>>(furniture)
{
  this->furniture = furniture.furniture;
}

FurnitureBy_UUID::FurnitureBy_UUID(std::shared_ptr<Furniture> furniture)
    : ValueBy_UUID<std::shared_ptr<Entity>>()
{
  this->furniture = furniture;
}

bool FurnitureBy_UUID::tryGetValue_ByUUID(
      IContainerUUID<std::shared_ptr<Entity>>& container, 
      std::shared_ptr<Entity> &value) 
{
  bool result = 
    ValueBy_UUID<std::shared_ptr<Entity>>::tryGetValue_ByUUID(
            container, value);
  if (result)
  {
    furniture = std::dynamic_pointer_cast<Furniture>(unsafeGet());
  }
  return result;
}
bool FurnitureBy_UUID::trySetActive(
      IContainerUUID<std::shared_ptr<Entity>> &container) 
{
  bool result = 
    ValueBy_UUID<std::shared_ptr<Entity>>::trySetActive(container);
  if (result)
  {
    furniture = std::dynamic_pointer_cast<Furniture>(unsafeGet());
  }
  return result;
}
