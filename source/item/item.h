#pragma once

#include <memory>
#include "../menu/listitem.h"
#include "../serialization/serializable.h"
#include "../serialization/serializer.h"

class Screen;
class Tile;
class Game;
class Level;
class Entity;
class Player;
class ItemEntity;

enum ItemKind
{
  IK_UNKNOWN = 0,
  IK_FURNITURE = 0xddd1,
  IK_POWERGLOVE = 0xddd2,
  IK_RESOURCE = 0xddd3,
  IK_TOOL = 0xddd4,
};

class Item : public ListItem, public ISerializeable
{
  enum ItemKind itemKind;
public:
  Item(enum ItemKind itemKind) : itemKind(itemKind) {}
  Item(Serializer &serializer) { serializer.loadFromFile(&itemKind); }

  virtual void initAfterLoad(Game &game) {}

  virtual std::string getName() const { return "ERROR"; }

  virtual int getColor() const { return 0; }

  virtual int getSprite() const { return 0; }

  virtual bool interact(Player &player, Entity &entity, int attackDir) { return false; }

  virtual void renderIcon(Screen &screen, int x, int y) {}

  virtual bool interactOn(Tile &tile, Level &level, int xt, int yt, Player &player, int attackDir) { return false; }

  virtual bool isDepleted() { return false; }

  virtual bool canAttack() { return false; }

  virtual int getAttackDamageBonus(Entity &e) { return 0; }

  virtual bool matches(const Item &item) { return item.getName() == getName(); }

  virtual std::shared_ptr<Item> clone() { return std::make_shared<Item>(itemKind); }

  enum ItemKind getKind() { return itemKind; }
  void serialize(Serializer &serializer) override { serializer.saveToFile(&itemKind); }
};
