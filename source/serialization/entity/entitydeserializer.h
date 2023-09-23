#pragma once

#include "../serializer.h"
#include "../../entity/entity.h"

#include <unordered_map>

#define BEGIN_DESERIALIZATION(serializer, baseType) \
    std::shared_ptr< baseType > result; \
    baseType *result_lookahead = serializer \
        .loadFromFile_Lookahead< baseType >(); \
    switch (result_lookahead->getKind()) { \
        default:

#define CASE_DESERIALIZE__WITH(kind, expr) \
        case kind: \
            result = expr ;\
            break;

#define CASE_DESERIALIZE__AS(kind, serializer, superType, baseType) \
        case kind: \
            result = std::static_pointer_cast< baseType > \
                (std::make_shared< superType > \
                    ( serializer )); \
            break;

#define END_DESERIALIZATION \
    } \
    return result;

#define END_DESERIALIZATION__AS(baseType) \
    } \
    return std::static_pointer_cast< baseType >( result );

namespace EntityDeserializer
{
  std::shared_ptr<Entity> deserialize(Serializer &serializer);
};
