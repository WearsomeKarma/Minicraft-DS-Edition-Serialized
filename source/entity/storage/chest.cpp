#include "chest.h"

#include "../../menu/furniture/storagemenu.h"

Chest::Chest(Serializer &serializer) 
: Furniture(serializer)
{
  inventory = std::make_shared<Inventory>(serializer);
}

Chest::Chest()
    : Furniture(FK_CHEST, "Chest")
{
  inventory = std::make_shared<Inventory>();
  col = Color::get(-1, 110, 331, 552);
  sprite = 1;
}

Chest::Chest(Game &game)
    : Chest()
{
  game.assignUUID(*this);
}

bool Chest::use(Game &game, Level &level, Player &player, int attackDir)
{
  game.enterMenu(std::make_unique<StorageMenu>(std::string("Chest"), inventory, game.player));
  return true;
}

std::shared_ptr<Furniture> Chest::clone(Game &game)
{
  return std::make_shared<Chest>(game);
}

void Chest::serialize(Serializer &serializer) 
{
  Furniture::serialize(serializer);
  inventory->serialize(serializer);
}

