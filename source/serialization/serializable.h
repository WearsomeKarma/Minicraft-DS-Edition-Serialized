#pragma once

#include <memory>

class I_UUID_Field;
class UUID_OwnedField;
class Serializer;
class IFactoryUUID;
class UUID;

class ISerializeable
{
public:
  virtual void serialize(Serializer &serializer) = 0;
};

class IHasUUID
{
public:
  virtual const I_UUID_Field &getUUID() const = 0;
};

class IOwnsUUID : public IHasUUID
{
protected:
  friend class IFactoryUUID;
  friend class Game;
  virtual bool recieveUUID(UUID_OwnedField &uuid) = 0; 
};
