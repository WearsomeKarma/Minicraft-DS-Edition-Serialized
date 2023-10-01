#pragma once

///
/// Any class which is capable of
/// assigning a UUID to a IOwnsUUID instance
///
#include "UUID.h"

class IAssignerUUID
{
public:
  virtual void assignUUID(IOwnsUUID &target) = 0;
};
