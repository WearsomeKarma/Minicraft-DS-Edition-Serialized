#include "entitydeserializer.h"

#include "../../item/inventory.h"

#include "furniture/furnituredeserializer.h"
#include "mob/mobdeserializer.h"
#include "particle/particledeserializer.h"
#include "item/itemdeserializer.h"

std::shared_ptr<Entity> EntityDeserializer::deserialize(Serializer &serializer)
{
  printf("\x1b[1;0HUTIL-ent-deser            ");
  BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, Entity)
    CASE_DESERIALIZE__WITH(
            EK_UNKNOWN, nullptr)
    CASE_DESERIALIZE__WITH(
            EK_FURNITURE, FurnitureDeserializer::deserialize(serializer))
    CASE_DESERIALIZE__WITH(
            EK_MOB, MobDeserializer::deserialize(serializer))
    CASE_DESERIALIZE__WITH(
            EK_PARTICLE, ParticleDeserializer::deserialize(serializer))
    CASE_DESERIALIZE__WITH(
            EK_ITEM, ItemEntityDeserializer::deserialize(serializer))
  END_DESERIALIZATION
  // printf("\x1b[1;0HUTIL-ent-deser %d           ", result_lookahead->getKind());

  // if (!result->hasInventory())
  //   return result;
  // printf("\x1b[1;0HUTIL-ent-deser %d inv       ", result_lookahead->getKind());

  // std::shared_ptr<Inventory> inventory =
  //     result->getInventory();
  // *inventory = Inventory(serializer);

  // return result;
}
