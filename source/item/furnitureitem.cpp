#include "furnitureitem.h"
#include "item.h"
#include <memory>
#include "../exception.h"
#include "../serialization/entity/furniture/furnituredeserializer.h"

FurnitureItem::FurnitureItem(Serializer &serializer)
    : Item(serializer)
{
  serializer.loadFromFile(&placed);
  if (placed)
  {
    furniture = FurnitureBy_UUID(serializer);
    return;
  }

  std::shared_ptr<Furniture> deserialized_furniture =
      std::static_pointer_cast<Furniture>(FurnitureDeserializer::deserialize(serializer));

  this->furniture = FurnitureBy_UUID(deserialized_furniture);
}

FurnitureItem::FurnitureItem(std::shared_ptr<Furniture> furniture)
    : Item(IK_FURNITURE), furniture(furniture) {}

void FurnitureItem::initAfterLoad(Game &game)
{
  //TODO: ifndef NDEBUG exception should be raised when return value is false.
  if (placed)
    furniture.trySetActive(game);  
}

std::string FurnitureItem::getName() const
{
  return furniture.unsafeAsFurniture()->name;
}

int FurnitureItem::getColor() const
{
  return furniture.unsafeAsFurniture()->col;
}

int FurnitureItem::getSprite() const
{
  return furniture.unsafeAsFurniture()->sprite + 10 * 32;
}

void FurnitureItem::renderIcon(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, getSprite(), getColor(), 0);
}

void FurnitureItem::renderInventory(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, getSprite(), getColor(), 0);
  screen.renderText(furniture.unsafeAsFurniture()->name, x + 8, y, Color::get(-1, 555, 555, 555));
}

bool FurnitureItem::canAttack()
{
  return false;
}

bool FurnitureItem::interactOn(Tile &tile, Level &level, int xt, int yt, Player &player, int attackDir)
{
  if (tile.mayPass(level, xt, yt, *furniture.unsafeAsFurniture()))
  {
    furniture.unsafeAsFurniture()->x = xt * 16 + 8;
    furniture.unsafeAsFurniture()->y = yt * 16 + 8;
    level.add(furniture.unsafeAsFurniture());
    placed = true;
    return true;
  }
  return false;
}

bool FurnitureItem::isDepleted()
{
  return placed;
}

bool FurnitureItem::matches(const Item &item)
{
  if (auto furnitureItem = dynamic_cast<const FurnitureItem *>(&item))
  {
    return furniture.getID() == furnitureItem->furniture.getID();
  }
  return false;
}

std::shared_ptr<Item> FurnitureItem::clone(Game &game)
{
  return std::make_shared<FurnitureItem>(furniture.unsafeAsFurniture()->clone(game));
}

void FurnitureItem::serialize(Serializer &serializer) 
{
  Item::serialize(serializer);
  serializer.saveToFile(&placed);
  if (placed) 
  {
    furniture.serialize(serializer);
    return;
  }

  furniture.unsafeAsFurniture()->serialize(serializer);
}
