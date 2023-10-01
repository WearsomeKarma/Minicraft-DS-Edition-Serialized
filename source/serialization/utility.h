#pragma once

#define BEGIN_DESERIALIZATION(serializer, baseType) \
    std::shared_ptr< baseType > result; \
    baseType *result_lookahead = serializer \
        .loadFromFile_Lookahead< baseType >(); \
    switch (result_lookahead->getKind()) { \
        default:

#define BEGIN_DESERIALIZATION__OF_SERIALIZEABLE(serializer, baseType) \
    std::shared_ptr< baseType > result; \
    baseType *result_lookahead = nullptr; \
    serializer \
        .loadFromFile_Lookahead_Serialized< baseType >(result_lookahead); \
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

#define END_DESERIALIZATION_CASES \
    }

#define END_DESERIALIZATION \
    } \
    return result;

#define END_DESERIALIZATION__AS(baseType) \
    } \
    return std::static_pointer_cast< baseType >( result );

#define RETURN_FROM_DESERIALIZATION__AS(baseType) \
    return std::static_pointer_cast< baseType >( result );
