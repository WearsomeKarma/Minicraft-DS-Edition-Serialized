#pragma once

#include <memory>

class UUID;
class Serializer;

class ISerializeable
{
public:
  virtual void serialize(Serializer &serializer) = 0;
  virtual void deserialize(Serializer &serializer) = 0;
  virtual std::shared_ptr<UUID> getUUID() { return nullptr; }
};
