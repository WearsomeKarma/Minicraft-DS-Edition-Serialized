#include "toolitem.h"

#include "../gfx/color.h"
#include "item.h"
#include "tooldetails.h"

ToolItem::ToolItem(Serializer &serializer)
    : Item(serializer)
{
  serializer.loadFromFile(&random);
  serializer.loadFromFile(&toolItemKind);
  switch (toolItemKind)
  {
  case TIK_UNKNOWN: //TODO impl
  case TIK_Axe:
      type = &ToolDetails::axe;
      break;
  case TIK_Hoe:
      type = &ToolDetails::hoe;
      break;
  case TIK_Pickaxe:
      type = &ToolDetails::pickaxe;
      break;
  case TIK_Sword:
      type = &ToolDetails::sword;
      break;
  case TIK_Shovel:
      type = &ToolDetails::shovel;
      break;
  }
}

std::string LEVEL_NAMES[5] = {
    "Wood", "Rock", "Iron", "Gold", "Gem"};

int LEVEL_COLORS[5] = {
    Color::get(-1, 100, 321, 431),
    Color::get(-1, 100, 321, 111),
    Color::get(-1, 100, 321, 555),
    Color::get(-1, 100, 321, 550),
    Color::get(-1, 100, 321, 055),
};

ToolItem::ToolItem(ToolDetails *type, int level)
    : Item(IK_TOOL)
{
  this->type = type;
  this->level = level;
  this->toolItemKind = type->toolItemKind;
}

std::string ToolItem::getName() const
{
  return LEVEL_NAMES[level] + " " + type->name;
}

int ToolItem::getColor() const
{
  return LEVEL_COLORS[level];
}

int ToolItem::getSprite() const
{
  return type->sprite + 5 * 32;
}

void ToolItem::renderIcon(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, getSprite(), getColor(), 0);
}

void ToolItem::renderInventory(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, getSprite(), getColor(), 0);
  screen.renderText(getName(), x + 8, y, Color::get(-1, 555, 555, 555));
}

bool ToolItem::canAttack()
{
  return true;
}

int ToolItem::getAttackDamageBonus(Entity &e)
{
  if (type == &ToolDetails::axe)
  {
    return (level + 1) * 2 + random.nextInt(4);
  }
  if (type == &ToolDetails::sword)
  {
    return (level + 1) * 3 + random.nextInt(2 + level * level * 2);
  }
  return 1;
}

bool ToolItem::matches(const Item &item)
{
  if (auto other = dynamic_cast<const ToolItem *>(&item))
  {
    if (other->type != type)
      return false;
    if (other->level != level)
      return false;
    return true;
  }
  return false;
}

std::shared_ptr<Item> ToolItem::clone()
{
  return std::make_shared<ToolItem>(type, level);
}

void ToolItem::serialize(Serializer &serializer)
{
  Item::serialize(serializer);
  serializer.saveToFile(&random);
  serializer.saveToFile(&toolItemKind);
}
