#pragma once

#include <memory>
#include "UUID.h"

template<typename TSharedPtr>
class IContainerUUID
{
public:
  virtual bool assignUUID(TSharedPtr &target) { return false; }
  virtual std::shared_ptr<TSharedPtr> getByUUID(UUID_Field &uuid) = 0;
};
