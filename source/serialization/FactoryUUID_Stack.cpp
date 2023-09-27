#include "FactoryUUID_Stack.h"
#include "UUID.h"
#include "serializable.h"
#include "serializer.h"
#include <cstddef>

FactoryUUID_Stack::FactoryUUID_Stack()
{
  availableIds.emplace_back(1);
}

FactoryUUID_Stack::FactoryUUID_Stack(Serializer &serializer)
{
  serializer.loadFromFile_Collection
      <std::vector<unsigned int>, unsigned int>(availableIds);
}

void FactoryUUID_Stack::freeUUID(UUID &uuid)
{
  availableIds.emplace_back(uuid.getID());
}

void FactoryUUID_Stack::assignUUID(ISerializeable_WithUUID &target)
{
  unsigned int id = availableIds.back();
  availableIds.erase(availableIds.end());
  if (availableIds.empty())
    availableIds.emplace_back(id + 1);
  performAssignmentOfUUID(target, makeUUID(id));
}

void FactoryUUID_Stack::serialize(Serializer &serializer)
{
  serializer.saveToFile_Collection
      <std::vector<unsigned int>, unsigned int>(availableIds);
}
