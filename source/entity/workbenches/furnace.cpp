#include "furnace.h"

#include "../../item/resourceitem.h"
#include "../../item/resource/resource.h"
#include "../../menu/furniture/craftingmenu.h"

static std::vector<std::shared_ptr<Recipe>> furnaceRecipes = {
    std::make_shared<Recipe>(std::make_unique<ResourceItem>(Resource::ironIngot), std::vector<ResourceItem>({ResourceItem(Resource::ironOre, 4), ResourceItem(Resource::coal, 1)})),
    std::make_shared<Recipe>(std::make_unique<ResourceItem>(Resource::goldIngot), std::vector<ResourceItem>({ResourceItem(Resource::goldOre, 4), ResourceItem(Resource::coal, 1)})),
    std::make_shared<Recipe>(std::make_unique<ResourceItem>(Resource::glass), std::vector<ResourceItem>({ResourceItem(Resource::sand, 4), ResourceItem(Resource::coal, 1)})),
};

Furnace::Furnace() : Furniture(FK_FURNACE, "Furnace")
{
  col = Color::get(-1, 000, 222, 333);
  sprite = 3;
  xr = 3;
  yr = 2;
}

Furnace::Furnace(Game &game)
    : Furnace()
{
  game.assignUUID(*this);
}

bool Furnace::use(Game &game, Level &level, Player &player, int attackDir)
{
  game.enterMenu(std::make_unique<CraftingMenu>(furnaceRecipes, player));
  return true;
}

std::shared_ptr<Furniture> Furnace::clone(Game &game)
{
  return std::make_shared<Furnace>(game);
}
