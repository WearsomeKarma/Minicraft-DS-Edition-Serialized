#include "itemdeserializer.h"

#include "../../item/furnitureitem.h"
#include "../../item/powergloveitem.h"
#include "../../item/resourceitem.h"
#include "../../item/toolitem.h"

std::shared_ptr<Item> ItemDeserializer::deserialize(Serializer &serializer)
{
  printf("\x1b[4;0HUTIL-item-deser            ");
  BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, Item)
    CASE_DESERIALIZE__WITH(IK_UNKNOWN, nullptr)
    CASE_DESERIALIZE__AS(IK_FURNITURE, serializer, FurnitureItem, Item)
    CASE_DESERIALIZE__AS(IK_TOOL, serializer, ToolItem, Item)
    CASE_DESERIALIZE__AS(IK_RESOURCE, serializer, ResourceItem, Item)
    CASE_DESERIALIZE__AS(IK_POWERGLOVE, serializer, PowerGloveItem, Item)
  END_DESERIALIZATION_CASES

  for (size_t i=0;i<10000;i++)
    printf("\x1b[1;0HINV-deser-item %ld         ", serializer.getPositionInFile());

  RETURN_FROM_DESERIALIZATION__AS(Item);
}
