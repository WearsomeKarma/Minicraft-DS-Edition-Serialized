#include "furniture.h"

#include <memory>
#include "entity.h"
#include "player.h"
#include "../item/furnitureitem.h"
#include "../item/powergloveitem.h"

Furniture::Furniture(Serializer &serializer)
: Entity(serializer)
{
  printf("\x1b[4;0HUTIL-item-deser 1A           "); \
  serializer.loadFromFile(&furnitureKind);
  printf("\x1b[4;0HUTIL-item-deser 1C           "); \
  serializer.loadFromFile(&col);
  printf("\x1b[4;0HUTIL-item-deser 1D           "); \
  serializer.loadFromFile(&sprite);
  printf("\x1b[4;0HUTIL-item-deser 1E           "); \

  size_t length;
  serializer.loadFromFile(&length);
  if (length == 0) return;
  printf("\x1b[4;0HUTIL-item-deser 1F %ld          ", serializer.getPositionInFile()); \
  char char_name[length];
  serializer.loadFromFile_Fields(&char_name[0], &char_name[length-1]);
  printf("\x1b[4;0HUTIL-item-deser 1G           "); \

  name.assign(&char_name[0], length);
  printf("\x1b[4;0HUTIL-item-deser 1H           "); \
}

Furniture::Furniture(enum FurnitureKind furnitureKind, std::string name)
: Entity(EK_FURNITURE), furnitureKind(furnitureKind)
{
  this->name = name;
  xr = 3;
  yr = 3;
}

void Furniture::tick(Game &game, Level &level, std::shared_ptr<Entity> self)
{
  if (pushDir == 0)
    move(level, 0, +1);
  if (pushDir == 1)
    move(level, 0, -1);
  if (pushDir == 2)
    move(level, -1, 0);
  if (pushDir == 3)
    move(level, +1, 0);
  pushDir = -1;
  if (pushTime > 0)
    pushTime--;

  if (shouldTake)
  {
    remove();

    game.player->inventory->add(
        game.player->getSelectedItemIndex(),
        std::make_shared<FurnitureItem>(std::static_pointer_cast<Furniture>(self)));

    shouldTake = false;
  }
}

void Furniture::render(Screen &screen)
{
  screen.renderTile(x - 8, y - 8 - 4, sprite * 2 + 8 * 32, col, 0);
  screen.renderTile(x - 0, y - 8 - 4, sprite * 2 + 8 * 32 + 1, col, 0);
  screen.renderTile(x - 8, y - 0 - 4, sprite * 2 + 8 * 32 + 32, col, 0);
  screen.renderTile(x - 0, y - 0 - 4, sprite * 2 + 8 * 32 + 33, col, 0);
}

bool Furniture::blocks(Entity &e)
{
  return true;
}

void Furniture::take(Player &player)
{
  if (std::dynamic_pointer_cast<PowerGloveItem>(player.getActiveItem()))
  {
    shouldTake = true;
  }
}

void Furniture::touchedBy(Level &level, Entity &entity)
{
  auto player = dynamic_cast<Player *>(&entity);

  if (player && pushTime == 0)
  {
    pushDir = player->dir;
    pushTime = 10;
  }
}

std::shared_ptr<Furniture> Furniture::clone()
{
  auto furniture = std::make_shared<Furniture>(furnitureKind, name);
  furniture->col = col;
  furniture->sprite = sprite;

  return furniture;
};

void Furniture::serialize(Serializer &serializer)
{
  Entity::serialize(serializer);
  serializer.saveToFile(&furnitureKind);
  serializer.saveToFile(&col);
  serializer.saveToFile(&sprite);

  size_t length = name.length();
  serializer.saveToFile(&length);
  if (length == 0) return;
  char char_name[length];

  serializer.saveToFile_Fields(&char_name[0], &char_name[length-1]);
}
