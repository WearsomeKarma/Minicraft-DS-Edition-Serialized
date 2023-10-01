#pragma once

#include "serializable.h"
#include "UUID.h"
#include "ContainerUUID.h"

template<typename TValue>
class ValueBy_UUID : public ISerializeable
{
  TValue value;
  UUID_ReferenceField reference_uuid;
  bool isActive = false;
public:
  ValueBy_UUID() {}
  ValueBy_UUID(UUID_ReferenceField reference_uuid)
    : reference_uuid(reference_uuid) {}
  ValueBy_UUID(TValue value, UUID_ReferenceField reference_uuid)
    : value(value), reference_uuid(reference_uuid) {}
  ValueBy_UUID(Serializer &serializer)
  {
    reference_uuid = UUID_ReferenceField(serializer);
  }
  unsigned int getID() const { return reference_uuid.getID(); }
  UUID_ReferenceField getUUID() const { return reference_uuid; }
  bool getIsActive() const { return isActive; }
  virtual bool tryGetValue_ByUUID(
          IContainerUUID<TValue>& container, TValue &value)
  {
    if (isActive)
    {
      value = this->value;
      return true;
    }
    if (!container.tryGetValue_ByUUID(reference_uuid, this->value))
      return false;
    value = this->value;
    return true;
  }
  virtual bool trySetActive(IContainerUUID<TValue> &container)
  {
    isActive = !container.tryGetValue_ByUUID(reference_uuid, this->value);
    return isActive;
  }
  TValue unsafeGet()
  { return value; }

  void serialize(Serializer &serializer) override
  {
    reference_uuid.serialize(serializer);
  }
};
