#pragma once

#include "serializable.h"
#include <memory>

class Serializer;

// Produced by an IFactoryUUID and given by weak_ptr.
class UUID final : public ISerializeable
{
private:
  friend class IFactoryUUID;
  static constexpr unsigned char _offset =
      sizeof(int) - sizeof(char);

  IFactoryUUID &source;
  unsigned int id;

  UUID(IFactoryUUID &source, unsigned int id) 
    : source(source), id(id)
  {}
public:
  unsigned int getID() const { return id; }

  UUID(Serializer &serializer);

  ~UUID();

  void serialize(Serializer &serializer) override;
};

class I_UUID_Field : public ISerializeable, public IHasUUID
{
public:
  virtual unsigned int getID() const = 0;
  const I_UUID_Field &getUUID() const override
  { return *this; }
};

class UUID_OwnedField : public I_UUID_Field 
{
protected:
  unsigned int id;
  std::shared_ptr<UUID> uuid_ptr;
  bool isActive = false;
public:
  UUID_OwnedField() : id(0) {}
  UUID_OwnedField(unsigned int id) : id(id) {}
  UUID_OwnedField(Serializer &serializer);
  UUID_OwnedField(std::shared_ptr<UUID> uuid_ptr)
      : uuid_ptr(uuid_ptr), isActive(true) {}
  
  ~UUID_OwnedField() {}
  
  virtual unsigned int getID() const override;
  bool getIsActive() const { return isActive; }
  bool getPtr(std::shared_ptr<UUID>& uuid_ptr);
 
  void serialize(Serializer &serializer) override;
};

class UUID_ReferenceField final : public I_UUID_Field
{
  unsigned int id;
public:
  UUID_ReferenceField() 
      : id(0) {}
  UUID_ReferenceField(unsigned int id) 
      : id(id) {}
  UUID_ReferenceField(Serializer &serializer);

  void serialize(Serializer &serializer) override;

  unsigned int getID() const override
  { return id; }
};

