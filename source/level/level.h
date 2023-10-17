#pragma once

#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include "tile/tile.h"
#include "../serialization/UUID.h"
#include "../serialization/serializable.h"
#include "../serialization/serializer.h"
#include "../serialization/FactoryUUID_Stack.h"
#include "../serialization/ContainerUUID.h"
#include "../game.h"
#include "../entity/player.h"
#include "../entity/entity.h"
#include "../shim/random.h"

class Screen;
class LightMask;

class Level : public ISerializeable,
    public IContainerUUID<std::shared_ptr<Entity>>,
    public IContainerUUID<std::weak_ptr<Entity>>
{
private:
  // Justification for no smartptr: 
  //   Game outlives all objects.
  //   Also, I don't want to retain a reference
  //   and thereby make Level a non-trivial type
  //   to construct.
  Game *game;

  Random random;
  signed char depth;

  void updateMap(int x, int y, int viewDistance);
  void sortAndRender(Screen &screen, std::vector<std::shared_ptr<Entity>> list);
  void insertEntity(int x, int y, std::shared_ptr<Entity> e);
  void removeEntity(int x, int y, std::shared_ptr<Entity> e);
  void renderBackground(Screen &screen, int xScroll, int yScroll);
  void renderSprites(Screen &screen, int xScroll, int yScroll);
  void renderLight(LightMask &screen, int xScroll, int yScroll);

public:
  int w, h;
  int grassColor = 141;
  int dirtColor = 322;
  int sandColor = 550;
  int monsterDensity = 8;
  std::shared_ptr<std::vector<unsigned char>> map;
  std::vector<unsigned char> tiles;
  std::vector<unsigned char> data;
  std::vector<std::shared_ptr<Entity>> entities;
  std::vector<std::vector<std::shared_ptr<Entity>>> entitiesInTiles;
  std::shared_ptr<Player> player;

  // For Serialization - DO NOT USE.
  Level(Serializer &serializer);
  // -------------------------------

  // utilize these
  Level(Game &game, int w, int h, signed char depth);
  Level(Game &game, int w, int h, signed char depth, Level &parentLevel);

  // For Deserialization - DO NOT USE.
  void initAfterLoad(Game &game);
  // ---------------------------------

  void tick(Game &game);
  void render(Screen &screen, LightMask &LightMask, Player &player);
  unsigned char getTile(int x, int y);
  void setTile(int x, int y, unsigned char tile, int dataVal);
  int getData(int x, int y);
  void setData(int x, int y, int val);
  void add(std::shared_ptr<Entity> entity);
  void remove(std::shared_ptr<Entity> e);
  void trySpawn(int count);
  char getDepth() { return depth; } 

  bool tryGetValue_ByUUID(I_UUID_Field &uuid, std::shared_ptr<Entity> &value) override;
  bool tryGetValue_ByUUID(I_UUID_Field &uuid, std::weak_ptr<Entity> &value) override;

  std::vector<std::shared_ptr<Entity>> getEntities(int x0, int y0, int x1, int y1);

  void serialize(Serializer &serializer) override;
};
