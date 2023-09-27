#include "mobdeserializer.h"

#include "../../../entity/hostile/airwizard.h"
#include "../../../entity/hostile/slime.h"
#include "../../../entity/hostile/zombie.h"
#include "../../../entity/player.h"

std::shared_ptr<Entity> MobDeserializer::deserialize(Serializer &serializer)
{
  BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, Mob)
      CASE_DESERIALIZE__AS(MK_AIRWIZARD, serializer, AirWizard, Mob)
      CASE_DESERIALIZE__AS(MK_SLIME, serializer, Slime, Mob)
      CASE_DESERIALIZE__AS(MK_ZOMBIE, serializer, Zombie, Mob)
      CASE_DESERIALIZE__AS(MK_PLAYER, serializer, Player, Mob)
  END_DESERIALIZATION__AS(Entity)
}
