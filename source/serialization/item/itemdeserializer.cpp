#include "itemdeserializer.h"

#include "../../item/furnitureitem.h"
#include "../../item/powergloveitem.h"
#include "../../item/resourceitem.h"
#include "../../item/toolitem.h"

std::shared_ptr<Item> ItemDeserializer::deserialize(Serializer &serializer)
{
  BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, Item)
    CASE_DESERIALIZE__WITH(IK_UNKNOWN, nullptr)
    CASE_DESERIALIZE__AS(IK_FURNITURE, serializer, FurnitureItem, Item)
    CASE_DESERIALIZE__AS(IK_TOOL, serializer, ToolItem, Item)
    CASE_DESERIALIZE__AS(IK_RESOURCE, serializer, ResourceItem, Item)
    CASE_DESERIALIZE__AS(IK_POWERGLOVE, serializer, PowerGloveItem, Item)
  END_DESERIALIZATION_CASES

  RETURN_FROM_DESERIALIZATION__AS(Item);
}
