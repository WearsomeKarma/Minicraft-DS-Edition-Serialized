#pragma once
#include <vector>

//
// Implementation of FactoryUUID, it uses a stack to
// keep track of IDs, it is also serializable.
//

#include "UUID.h"
#include "serializable.h"
#include "serializer.h"
#include "FactoryUUID.h"

class FactoryUUID_Stack : public IFactoryUUID, public ISerializeable
{
private:
  // concrete type of vector, but we instrinsicly treat it as a stack
  std::vector<unsigned int> availableIds;
protected:
  void freeUUID(UUID &uuid) override;
public:
  FactoryUUID_Stack();
  FactoryUUID_Stack(Serializer &serializer);

  void assignUUID(IOwnsUUID &target) override;

  void serialize(Serializer &serializer) override;
};
