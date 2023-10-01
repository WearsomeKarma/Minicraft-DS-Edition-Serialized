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
// protected:
public:
  std::shared_ptr<UUID> makeUUID(unsigned int id) 
  { return std::shared_ptr<UUID>(new UUID(*this, id)); }
  void performAssignmentOfUUID(
          IOwnsUUID &target, std::shared_ptr<UUID> uuid)
  { 
    UUID_OwnedField owned_uuid = UUID_OwnedField(uuid);
    target.recieveUUID(owned_uuid); 
  }
public:
  virtual void assignUUID(IOwnsUUID &target) = 0;
};
