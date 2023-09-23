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

class ISerializeable_WithUUID : public ISerializeable
{
public:
  virtual const UUID_Field &getUUID() const = 0;
protected:
  friend class IFactoryUUID;
  // return true if you actually keep the uuid given to you.
  virtual UUID_Field &getUUID() = 0; 
};
