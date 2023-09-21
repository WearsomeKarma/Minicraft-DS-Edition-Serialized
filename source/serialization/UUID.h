#pragma once

#include "serializable.h"
#include <memory>

class IFactoryUUID;
class UUID : public ISerializeable
{
private:
  friend class IFactoryUUID;
  static constexpr unsigned char _offset =
      sizeof(int) - sizeof(char);

  IFactoryUUID &originiatingFactory;
  unsigned int id;

  UUID(IFactoryUUID &originiatingFactory, unsigned int id) 
      : originiatingFactory(originiatingFactory),
    id(id)
  {}
public:
  unsigned int getID() { return id; }

  ~UUID();

  void serialize(Serializer &serializer) override;
  void deserialize(Serializer &serializer) override;
};

class IFactoryUUID
{
protected:
  friend class UUID;
  virtual void freeUUID(UUID &uuid) = 0;
  std::shared_ptr<UUID> constructUUID(unsigned int id) 
  { return std::shared_ptr<UUID>(new UUID(*this, id)); }
public:
  virtual std::shared_ptr<UUID> getNewUUID() = 0;
};
