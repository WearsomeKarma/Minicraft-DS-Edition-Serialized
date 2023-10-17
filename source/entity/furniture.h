#pragma once

#include <memory>
#include "entity.h"
#include "player.h"

enum FurnitureKind
{
  FK_UNKNOWN = 0,
  FK_ANVIL,
  FK_CHEST,
  FK_FURNACE,
  FK_LANTERN,
  FK_OVEN,
  FK_WORKBENCH,
};

class Furniture : public Entity
{
  enum FurnitureKind furnitureKind;
public:
  int col, sprite;
  std::string name;

  Furniture(Serializer &serializer);
  Furniture(enum FurnitureKind furnitureKind, std::string name);
  Furniture(Furniture &f);

  virtual ~Furniture() {}

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;

  void render(Screen &screen) override;
  bool blocks(Entity &e) override;
  void take(Player &player);
  virtual std::shared_ptr<Furniture> clone(Game &game);

  enum FurnitureKind getKind() { return furnitureKind; }

  void serialize(Serializer &serializer) override;

protected:
  bool shouldTake = false;
  void touchedBy(Level &level, Entity &entity) override;

private:
  int pushTime = 0;
  int pushDir = -1;
};
