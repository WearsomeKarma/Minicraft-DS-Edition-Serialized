#include "FactoryUUID_Stack.h"
#include "UUID.h"
#include <cstddef>

void FactoryUUID_Stack::freeUUID(UUID &uuid)
{
  availableIds.emplace_back(uuid.getID());
}

std::shared_ptr<UUID> FactoryUUID_Stack::getNewUUID()
{
  unsigned int id = availableIds.back();
  availableIds.erase(availableIds.end());
  if (availableIds.empty())
    availableIds.emplace_back(id + 1);
  return constructUUID(id);
}

void FactoryUUID_Stack::serialize(Serializer &serializer)
{
  size_t length = availableIds.size();
  serializer.saveToFile(&length);
  for(auto id : availableIds)
    serializer.saveToFile(&id);
}

void FactoryUUID_Stack::deserialize(Serializer &serializer)
{
  size_t length;
  serializer.loadFromFile(&length);
  for(size_t i=0;i<length;i++)
  {
    serializer.loadFromFile_EmplaceBack
        <unsigned int, std::list<unsigned int>>(availableIds);
  }
}
