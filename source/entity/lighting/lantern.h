#pragma once

#include "../furniture.h"

class Lantern : public Furniture
{
public:
  Lantern();
  Lantern(Serializer &serializer)
      : Furniture(serializer)
  {}

  int getLightRadius() override;
  std::shared_ptr<Furniture> clone() override;
};
