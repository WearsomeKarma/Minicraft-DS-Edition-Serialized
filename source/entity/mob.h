#pragma once

#include "entity.h"

enum MobKind
{
  MK_UNKNOWN = 0,
  MK_AIRWIZARD,
  MK_SLIME,
  MK_ZOMBIE,
  MK_PLAYER,
};

class Mob : public Entity
{
  enum MobKind mobKind;
protected:
  int walkDist = 0;
  int xKnockback = 0;
  int yKnockback = 0;

  virtual void doHurt(Level &level, int damage, int attackDir);
  virtual void die(Game &game, Level &level);
  virtual bool isSwimming(Level &level);

  int xa, ya;
  int randomWalkTime = 0;
  int attackDelay = 0;
  int attackTime = 0;
  int attackType = 0;

  int jumpTime = 0;
  int lvl;

public:
  int hurtTime = 0;
  int maxHealth = 10;
  int health = maxHealth;
  int swimTimer = 0;
  int tickTime = 0;
  int dir = 0;

  // USED FOR DESERIALIZATION!!! DO NOT USE!!!
  Mob() {}
  // -----------------------------------------

  Mob(enum MobKind mobKind);
  Mob(Serializer &serializer);

  void tick(Game &game, Level &level, std::shared_ptr<Entity> self) override;
  bool move(Level &, int xa, int ya) override;
  bool blocks(Entity &e) override;
  void hurt(Level &level, Tile &tile, int x, int y, int damage) override;
  void hurt(Level &level, Mob &mob, int damage, int attackDir);
  void heal(Level &level, int heal);
  bool findStartPos(Level &level);

  enum MobKind getKind() const { return mobKind; }

  void serialize(Serializer &serializer) override;
};
