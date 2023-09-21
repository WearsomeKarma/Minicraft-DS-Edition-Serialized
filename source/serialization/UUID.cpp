#include "UUID.h"

UUID::~UUID()
{
  originiatingFactory.freeUUID(*this);
}

void UUID::serialize(Serializer &serializer) 
{
  
}
void UUID::deserialize(Serializer &serializer) 
{

}
