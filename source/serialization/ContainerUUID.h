#pragma once

#include <memory>
#include "UUID.h"

template<typename TValue>
class IContainerUUID
{
public:
  virtual bool assignUUID(TValue &target) { return false; }
  virtual TValue getByUUID(UUID_Field &uuid) = 0;
};
