#pragma once

#include <memory>

class UUID;
class UUID_Field;
class Serializer;
class IFactoryUUID;

class ISerializeable
{
public:
  virtual void serialize(Serializer &serializer) = 0;
};

class IHasUUID
{
public:
  virtual const UUID_Field &getUUID() const = 0;
};

class IOwnsUUID : public IHasUUID
{
protected:
  friend class IFactoryUUID;
  // return true if you actually keep the uuid given to you.
  virtual UUID_Field &getUUID() = 0; 
};

template<typename TValue>
class IContainerUUID;

template<typename TValue>
class IReferencesUUID : public IHasUUID
{
protected:
  friend class IContainerUUID<TValue>;
  virtual void resolveValueOfUUID(
          IContainerUUID<TValue>& container) = 0;
};

template<typename TValue>
class IDependentsReferenceUUIDs
{
protected:
  friend class IContainerUUID<TValue>;
  virtual void handleDependentsResolutionOfUUIDs(
          IContainerUUID<TValue>& container) = 0;
};

class ISerializeable_WithUUID : public ISerializeable, public IOwnsUUID
{};
