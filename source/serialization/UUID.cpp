#include "UUID.h"
#include "serializer.h"

UUID_Field::UUID_Field() 
: uuid_ptr(std::weak_ptr<UUID>()) {}

UUID_Field::UUID_Field(unsigned int id) 
: id(id) {}

UUID_Field::UUID_Field(std::weak_ptr<UUID> uuid_ptr) 
: uuid_ptr(uuid_ptr), isActive(true) {}

UUID_Field::UUID_Field(Serializer &serializer)
: id(0)
{
  serializer.loadFromFile(&id);
}

UUID_Field::UUID_Field(const UUID_Field &field)
{
  isActive = field.isActive;
  if (isActive)
    uuid_ptr = field.uuid_ptr;
  else
    id = field.id;
}

UUID_Field::UUID_Field(UUID_Field &field)
: UUID_Field((const UUID_Field&)field)
{}

UUID_Field& UUID_Field::operator=(UUID_Field field)
{
  if (this == &field) return *this;
  isActive = field.isActive;
  if (isActive)
    uuid_ptr = field.uuid_ptr;
  else
    id = field.id;
  return *this;
}

unsigned int UUID_Field::getID() const
{
  return isActive
      ? uuid_ptr.lock()->getID()
      : id
      ;
}

bool UUID_Field::getPtr(std::weak_ptr<UUID>& uuid_ptr)
{
  if (!isActive)
    return false;
  uuid_ptr = uuid_ptr;
  return true;
}

void UUID_Field::serialize(Serializer &serializer)
{
  unsigned int id = getID();
  serializer.saveToFile(&id);
}
