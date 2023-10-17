#include "recipe.h"

#include "../resourceitem.h"
#include "../../entity/player.h"
#include "../furnitureitem.h"

Recipe::Recipe(std::unique_ptr<Item> result, std::vector<ResourceItem> requirements)
    : result(std::move(result)), requirements(requirements) {}

void Recipe::checkCanCraft(Player &player)
{
  for (auto &item : requirements)
  {
    if (auto resourceItem = dynamic_cast<const ResourceItem *>(&item))
    {
      if (!player.inventory->hasResources(resourceItem->resourceId, resourceItem->count))
      {
        canCraft = false;
        return;
      }
    }
  }
  canCraft = true;
}

void Recipe::craft(Game &game, Player &player)
{
  player.inventory->add(result->clone(game));

  for (auto &item : requirements)
  {
    if (auto resourceItem = dynamic_cast<const ResourceItem *>(&item))
    {
      player.inventory->removeResource(resourceItem->resourceId, resourceItem->count);
    }
  }
}

void Recipe::renderInventory(Screen &screen, int x, int y)
{
  screen.renderTile(x, y, result->getSprite(), result->getColor(), 0);
  int textColor = canCraft ? Color::get(-1, 555, 555, 555) : Color::get(-1, 222, 222, 222);
  screen.renderText(result->getName(), x + 8, y, textColor);
}
