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
class Inventory;

enum EntityKind
{
  EK_UNKNOWN = 0,
  EK_FURNITURE = 0xeee1,
  EK_MOB = 0xeee2,
  EK_PARTICLE = 0xeee3,
  EK_ITEM = 0xeee4
};

class Entity : public ISerializeable, public IOwnsUUID
{
  UUID_OwnedField uuid;
  enum EntityKind entityKind;
protected:
  static Random random;

  bool move2(Level &level, int xa, int ya);

public:
  int x, y;
  int xr = 6;
  int yr = 6;
  bool removed = false;

  Entity(enum EntityKind entityKind) : entityKind(entityKind) {}
  Entity(enum EntityKind entityKind, int x, int y)
    : entityKind(entityKind), x(x), y(y) {}
  Entity(Serializer &serializer);

  virtual ~Entity() {}

  bool interact(Player &player, Item &item, int attackDir);
  void remove();
  bool intersects(int x0, int y0, int x1, int y1);

  virtual void initAfterLoad(Game &game);

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

  virtual bool hasInventory() { return false; }
  virtual std::shared_ptr<Inventory> getInventory() { return nullptr; }
  enum EntityKind getKind() const { return entityKind; }

  void serialize(Serializer &serializer) override;

  const I_UUID_Field &getUUID() const override 
  { return uuid; }

protected:
  bool recieveUUID(UUID_OwnedField &uuid) override;
};
