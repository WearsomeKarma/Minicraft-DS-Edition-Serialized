#include "workbench.h"

#include "../lighting/lantern.h"
#include "oven.h"
#include "furnace.h"
#include "anvil.h"
#include "../storage/chest.h"
#include "../../item/toolitem.h"
#include "../../item/furnitureitem.h"
#include "../../menu/furniture/craftingmenu.h"

static std::vector<std::shared_ptr<Recipe>> workbenchRecipes = {
    std::make_shared<Recipe>(std::make_unique<FurnitureItem>(std::make_shared<Lantern>()), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::slime, 10), ResourceItem(Resource::glass, 4)})),
    std::make_shared<Recipe>(std::make_unique<FurnitureItem>(std::make_shared<Oven>()), std::vector<ResourceItem>({ResourceItem(Resource::stone, 15)})),
    std::make_shared<Recipe>(std::make_unique<FurnitureItem>(std::make_shared<Furnace>()), std::vector<ResourceItem>({ResourceItem(Resource::stone, 20)})),
    std::make_shared<Recipe>(std::make_unique<FurnitureItem>(std::make_shared<Workbench>()), std::vector<ResourceItem>({ResourceItem(Resource::wood, 20)})),
    std::make_shared<Recipe>(std::make_unique<FurnitureItem>(std::make_shared<Chest>()), std::vector<ResourceItem>({ResourceItem(Resource::wood, 20)})),
    std::make_shared<Recipe>(std::make_unique<FurnitureItem>(std::make_shared<Anvil>()), std::vector<ResourceItem>({ResourceItem(Resource::ironIngot, 5)})),

    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::sword, 0), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::axe, 0), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::hoe, 0), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::pickaxe, 0), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::shovel, 0), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5)})),

    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::sword, 1), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::stone, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::axe, 1), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::stone, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::hoe, 1), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::stone, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::pickaxe, 1), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::stone, 5)})),
    std::make_shared<Recipe>(std::make_unique<ToolItem>(&ToolDetails::shovel, 1), std::vector<ResourceItem>({ResourceItem(Resource::wood, 5), ResourceItem(Resource::stone, 5)})),
};

Workbench::Workbench() : Furniture(FK_WORKBENCH, "Workbench")
{
  col = Color::get(-1, 100, 321, 431);
  sprite = 4;
  xr = 3;
  yr = 2;
}

Workbench::Workbench(Game &game)
    : Workbench()
{
  game.assignUUID(*this);
}

bool Workbench::use(Game &game, Level &level, Player &player, int attackDir)
{
  game.enterMenu(std::make_unique<CraftingMenu>(workbenchRecipes, player));
  return true;
}

std::shared_ptr<Furniture> Workbench::clone(Game &game)
{
  return std::make_shared<Workbench>(game);
}
