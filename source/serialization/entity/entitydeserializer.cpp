#include "entitydeserializer.h"
#include "furniture/furnituredeserializer.h"
#include "mob/mobdeserializer.h"
#include "particle/particledeserializer.h"
#include "item/itemdeserializer.h"

std::shared_ptr<Entity> EntityDeserializer::deserialize(Serializer &serializer)
{
    BEGIN_DESERIALIZATION(serializer, Entity)
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
}
