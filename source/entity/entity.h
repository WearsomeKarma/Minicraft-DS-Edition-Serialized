#pragma once

#include "../shim/random.h"
#include "../serialization/UUID.h"
#include "../serialization/serializable.h"
#include "../serialization/serializer.h"

#include <memory>

class Game;
class Screen;
class Level;
class Tile;
class Player;
class Item;
class ItemEntity;
class Mob;

enum EntityKind
{
  EK_UNKNOWN = 0,
  EK_FURNITURE,
  EK_MOB,
  EK_PARTICLE,
  EK_ITEM
};

class Entity : public ISerializeable_WithUUID
{
  UUID_Field uuid;
  enum EntityKind entityKind;
protected:
  static Random random;

  bool move2(Level &level, int xa, int ya);

public:
  int x, y;
  int xr = 6;
  int yr = 6;
  bool removed = false;

  // USED FOR DESERIALIZATION!!! DO NOT USE!!!
  Entity() {}
  // -----------------------------------------

  Entity(enum EntityKind entityKind) : entityKind(entityKind) {}
  Entity(enum EntityKind entityKind, int x, int y)
    : entityKind(entityKind), x(x), y(y) {}
  Entity(Serializer &serializer);

  bool interact(Player &player, Item &item, int attackDir);
  void remove();
  bool intersects(int x0, int y0, int x1, int y1);

  virtual void tick(Game &game, Level &level, std::shared_ptr<Entity> self) {}
  virtual void render(Screen &screen) {}
  virtual bool move(Level &level, int xa, int ya);
  virtual bool blocks(Entity &e) { return false; }
  virtual void hurt(Level &level, Mob &mob, int dmg, int attackDir) {}
  virtual void hurt(Level &level, Tile &tile, int x, int y, int dmg) {}
  virtual void touchedBy(Level &level, Entity &entity){};
  virtual bool isBlockableBy(Mob &mob) { return true; }
  virtual void touchItem(ItemEntity &itemEntity) {}
  virtual bool canSwim() { return false; }
  virtual bool use(Game &game, Level &level, Player &player, int attackDir) { return false; }
  virtual int getLightRadius() { return 0; }

  enum EntityKind getKind() const { return entityKind; }

  void serialize(Serializer &serializer) override;

  const UUID_Field &getUUID() const override 
  { return uuid; }

protected:
  UUID_Field &getUUID() override 
  { return uuid; }
};
