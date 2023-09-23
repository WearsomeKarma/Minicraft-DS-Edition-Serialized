#pragma once

#include "../serialization/UUID.h"
#include "../serialization/ContainerUUID.h"

template<class TSmartPtr, typename TEntityType>
class Reference_ByUUID_Entity : public ISerializeable_WithUUID
{
  UUID_Field uuid;
  TSmartPtr entity_ptr;
public:
  Reference_ByUUID_Entity() {}
  Reference_ByUUID_Entity(const UUID_Field& uuid_ref) 
  {
    uuid = uuid_ref;
  }
  Reference_ByUUID_Entity(Serializer &serializer)
  {
    uuid = UUID_Field(serializer);
  }

  std::weak_ptr< TEntityType > get(IContainerUUID< TEntityType > &container)
  {
    if (!entity_ptr.expired())
      return entity_ptr;
    return entity_ptr = 
        TSmartPtr(container.getByUUID(uuid));
  }

  void serialize(Serializer &serializer) override
  {
    uuid.serialize(serializer);
  }

  const UUID_Field &getUUID() const override 
  { return uuid; }
protected:
  UUID_Field &getUUID() override 
  { return uuid; }
};

template<typename TEntityType>
class WeakReference_ByUUID_Entity : 
    public Reference_ByUUID_Entity<std::weak_ptr<TEntityType>, TEntityType>
{
public:
  WeakReference_ByUUID_Entity() {}
  WeakReference_ByUUID_Entity(const UUID_Field& uuid_owner)
      : Reference_ByUUID_Entity
        <std::weak_ptr<TEntityType>, TEntityType>(uuid_owner) {}
};

template<typename TEntityType>
class SharedReference_ByUUID_Entity : 
    public Reference_ByUUID_Entity<std::shared_ptr<TEntityType>, TEntityType>
{
public:
  SharedReference_ByUUID_Entity() {}
  SharedReference_ByUUID_Entity(const UUID_Field& uuid_owner)
      : Reference_ByUUID_Entity
        <std::weak_ptr<TEntityType>, TEntityType>(uuid_owner) {}
};
