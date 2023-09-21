#pragma once
#include <list>

//
// Implementation of FactoryUUID, it uses a stack to
// keep track of IDs, it is also serializable.
//

#include "UUID.h"
#include "serializable.h"
#include "serializer.h"
class FactoryUUID_Stack : public IFactoryUUID, public ISerializeable
{
private:
  // concrete type of vector, but we instrinsicly treat it as a stack
  std::list<unsigned int> availableIds;
protected:
  void freeUUID(UUID &uuid) override;
public:
  FactoryUUID_Stack();

  std::shared_ptr<UUID> getNewUUID() override;

  void serialize(Serializer &serializer) override;
  void deserialize(Serializer &serializer) override;
};
