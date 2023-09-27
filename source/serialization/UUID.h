#pragma once

#include "serializable.h"
#include <memory>

// Produced by an IFactoryUUID and given by weak_ptr.
class UUID final
{
private:
  friend class IFactoryUUID;
  static constexpr unsigned char _offset =
      sizeof(int) - sizeof(char);

  const unsigned int id;

  UUID(unsigned int id) 
    : id(id)
  {}
public:
  unsigned int getID() const { return id; }
};

class UUID_Field final : public ISerializeable_WithUUID
{
  union
  {
    unsigned int id;
    std::weak_ptr<UUID> uuid_ptr;
  };
  bool isActive = false;

public:
  UUID_Field();
  UUID_Field(Serializer &serializer);
  UUID_Field(unsigned int id);
  UUID_Field(std::weak_ptr<UUID> uuid_ptr);

  UUID_Field(UUID_Field &field);
  UUID_Field& operator=(UUID_Field field);
  UUID_Field(const UUID_Field &field);

  ~UUID_Field() {}

  bool getIsActive() const { return isActive; }
  unsigned int getID() const;
  bool getPtr(std::weak_ptr<UUID>& uuid_ptr);

  void serialize(Serializer &serializer) override;
  const UUID_Field &getUUID() const override
  { return *this; }

protected:
  UUID_Field &getUUID() override
  { return *this; }
};
