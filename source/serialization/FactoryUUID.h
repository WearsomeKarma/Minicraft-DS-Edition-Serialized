#pragma once

#include <memory>
#include "UUID.h"
#include "serializable.h"

#define UUID_BEGINNING 1
#define UUID_NULL 0

class IFactoryUUID
{
protected:
  friend class UUID;
  virtual void freeUUID(UUID &uuid) = 0;
  std::shared_ptr<UUID> makeUUID(unsigned int id) 
  { return std::shared_ptr<UUID>(new UUID(id)); }
  void performAssignmentOfUUID(ISerializeable_WithUUID &target, std::weak_ptr<UUID> uuid)
  { target.getUUID() = UUID_Field(uuid); }
public:
  virtual void assignUUID(ISerializeable_WithUUID &target) = 0;
};
