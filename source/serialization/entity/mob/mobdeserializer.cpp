#include "mobdeserializer.h"

#include "../../../entity/hostile/airwizard.h"
#include "../../../entity/hostile/slime.h"
#include "../../../entity/hostile/zombie.h"
#include "../../../entity/player.h"

std::shared_ptr<Entity> MobDeserializer::deserialize(Serializer &serializer)
{
  printf("\x1b[2;0HUTIL-ent-mob-deser           ");
  BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, Mob)
    CASE_DESERIALIZE__WITH(MK_UNKNOWN, nullptr)
    CASE_DESERIALIZE__AS(MK_AIRWIZARD, serializer, AirWizard, Mob)
    CASE_DESERIALIZE__AS(MK_SLIME, serializer, Slime, Mob)
    CASE_DESERIALIZE__AS(MK_ZOMBIE, serializer, Zombie, Mob)
    CASE_DESERIALIZE__AS(MK_PLAYER, serializer, Player, Mob)
  END_DESERIALIZATION_CASES

  printf("\x1b[2;0HUTIL-ent-mob-deser %d        ", result_lookahead->getKind());
  RETURN_FROM_DESERIALIZATION__AS(Entity)
}
