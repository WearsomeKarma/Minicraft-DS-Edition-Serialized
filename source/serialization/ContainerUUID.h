#pragma once

#include <memory>
#include "UUID.h"
#include "serializable.h"

template<typename TValue>
class IContainerUUID
{
public:
  virtual bool tryGetValue_ByUUID(I_UUID_Field &uuid, TValue &value) = 0;
};
