#include "furnitureitem.h"
#include "item.h"
#include <memory>
#include "../exception.h"

FurnitureItem::FurnitureItem(Serializer &serializer)
    : Item(IK_FURNITURE)
{
  furniture_uuid = UUID_Field(serializer);
  serializer.loadFromFile(&placed);
}

FurnitureItem::FurnitureItem(std::shared_ptr<Furniture> furniture)
    : Item(IK_FURNITURE), furniture(furniture), furniture_uuid(((const Furniture&)*furniture).getUUID()) {}

std::string FurnitureItem::getName() const
{
  return furniture->name;
}

int FurnitureItem::getColor() const
{
  return furniture->col;
}

int FurnitureItem::getSprite() const
{
  return furniture->sprite + 10 * 32;
}

void FurnitureItem::renderIcon(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, getSprite(), getColor(), 0);
}

void FurnitureItem::renderInventory(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, getSprite(), getColor(), 0);
  screen.renderText(furniture->name, x + 8, y, Color::get(-1, 555, 555, 555));
}

bool FurnitureItem::canAttack()
{
  return false;
}

bool FurnitureItem::interactOn(Tile &tile, Level &level, int xt, int yt, Player &player, int attackDir)
{
  if (tile.mayPass(level, xt, yt, *furniture))
  {
    furniture->x = xt * 16 + 8;
    furniture->y = yt * 16 + 8;
    level.add(furniture);
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
  if (!furniture_uuid.getIsActive())
    return false;
  if (auto furnitureItem = dynamic_cast<const FurnitureItem *>(&item))
  {
    return furniture_uuid.getID() == furnitureItem->furniture_uuid.getID();
  }
  return false;
}

std::shared_ptr<Item> FurnitureItem::clone()
{
  return std::make_shared<FurnitureItem>(furniture->clone());
}

void FurnitureItem::serialize(Serializer &serializer) 
{
  furniture_uuid.serialize(serializer);
  serializer.saveToFile(&placed);
}

void FurnitureItem::resolveValueOfUUID(
        IContainerUUID<std::shared_ptr<Entity>>& container)
{
  furniture = std::dynamic_pointer_cast<Furniture>(
          container.getByUUID(furniture_uuid));
  if (!furniture)
  {
    printf("\x1b[11;0HFurnitureItem.resolveValueOfUUID is nullptr");
    Exception::raise();
  }
}
