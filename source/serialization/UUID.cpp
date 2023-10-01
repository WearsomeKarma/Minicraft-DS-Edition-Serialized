#include "UUID.h"
#include "serializer.h"
#include "../game.h"

UUID::UUID(Serializer &serializer)
    : source(serializer.game.factoryUUID)
{
  serializer.loadFromFile(&id);
}

void UUID::serialize(Serializer &serializer)
{
serializer.saveToFile(&id);
}

UUID::~UUID()
{
  source.freeUUID(*this);
}

UUID_ReferenceField::UUID_ReferenceField(Serializer &serializer)
{
  serializer.loadFromFile(&id);
}

void UUID_ReferenceField::serialize(Serializer &serializer)
{
  serializer.saveToFile(&id);
}

UUID_OwnedField::UUID_OwnedField(Serializer &serializer)
{
  serializer.loadFromFile(&isActive);
  if (!isActive)
  {
    unsigned int id = 0;
    serializer.loadFromFile(&id);
    *this = UUID_OwnedField(id);
    return;
  }
  *this = UUID_OwnedField(std::make_shared<UUID>(serializer));
}

unsigned int UUID_OwnedField::getID() const 
{
  return isActive
      ? uuid_ptr->getID()
      : id
      ;
}

bool UUID_OwnedField::getPtr(std::shared_ptr<UUID>& uuid_ptr)
{
  if (!isActive)
    return false;
  this->uuid_ptr = uuid_ptr;
  return true;
}

void UUID_OwnedField::serialize(Serializer &serializer)
{
  serializer.saveToFile(&isActive);
  if (isActive)
  {
    unsigned int id = uuid_ptr->getID();
    serializer.saveToFile(&id);
  }
  else
    serializer.saveToFile(&this->id);
}
