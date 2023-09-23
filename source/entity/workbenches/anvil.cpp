#include "anvil.h"

#include "../../item/toolitem.h"
#include "../../menu/furniture/craftingmenu.h"

static std::vector<std::shared_ptr<Recipe>> anvilRecipes = {
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::sword, 2), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::ironIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::axe, 2), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::ironIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::hoe, 2), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::ironIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::pickaxe, 2), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::ironIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::shovel, 2), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::ironIngot, 5)})),

    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::sword, 3), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::goldIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::axe, 3), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::goldIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::hoe, 3), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::goldIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::pickaxe, 3), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::goldIngot, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::shovel, 3), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::goldIngot, 5)})),

    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::sword, 4), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::gem, 50)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::axe, 4), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::gem, 50)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::hoe, 4), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::gem, 50)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::pickaxe, 4), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::gem, 50)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::shovel, 4), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::gem, 50)})),
};

Anvil::Anvil()
    : Furniture(FK_ANVIL, "Anvil")
{
  col = Color::get(-1, 000, 111, 222);
  sprite = 0;
  xr = 3;
  yr = 2;
}

bool Anvil::use(Game &game, Level &level, Player &player, int attackDir)
{
  game.enterMenu(std::make_unique<CraftingMenu>(anvilRecipes, player));
  return true;
}

std::shared_ptr<Furniture> Anvil::clone()
{
  return std::make_shared<Anvil>();
}
