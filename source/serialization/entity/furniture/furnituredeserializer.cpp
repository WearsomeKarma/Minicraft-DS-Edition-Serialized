#include "furnituredeserializer.h"

#include "../../../entity/furniture.h"
#include "../../../entity/storage/chest.h"
#include "../../../entity/workbenches/anvil.h"
#include "../../../entity/lighting/lantern.h"
#include "../../../entity/workbenches/furnace.h"
#include "../../../entity/workbenches/oven.h"
#include "../../../entity/workbenches/workbench.h"

std::shared_ptr<Entity> FurnitureDeserializer::deserialize(
        Serializer &serializer)
{
  BEGIN_DESERIALIZATION(serializer, Furniture)
      CASE_DESERIALIZE__WITH(FK_UNKNOWN, nullptr)
      CASE_DESERIALIZE__AS(FK_ANVIL, serializer, Anvil, Furniture)
      CASE_DESERIALIZE__AS(FK_CHEST, serializer, Chest, Furniture)
      CASE_DESERIALIZE__AS(FK_FURNACE, serializer, Furnace, Furniture)
      CASE_DESERIALIZE__AS(FK_LANTERN, serializer, Lantern, Furniture)
      CASE_DESERIALIZE__AS(FK_OVEN, serializer, Oven, Furniture)
      CASE_DESERIALIZE__AS(FK_WORKBENCH, serializer, Workbench, Furniture)
  END_DESERIALIZATION__AS(Entity)
}
