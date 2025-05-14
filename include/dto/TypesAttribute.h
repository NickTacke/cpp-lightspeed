#ifndef LIGHTSPEED_DTOS_TYPESATTRIBUTE_H
#define LIGHTSPEED_DTOS_TYPESATTRIBUTE_H

#include <nlohmann/json.hpp>
#include <string>

#include "Attribute.h"
#include "Resource.h"
#include "Type.h"

namespace Lightspeed {
namespace dto {

struct TypesAttribute {
    int id;
    int sortOrder;
    Resource<Type> type;
    Resource<Attribute> attribute;
};

inline void from_json(const nlohmann::json &j, TypesAttribute &a) {
    j.at("id").get_to(a.id);
    j.at("sortOrder").get_to(a.sortOrder);
    j.at("type").get_to(a.type);
    j.at("attribute").get_to(a.attribute);
}

inline void to_json(nlohmann::json &j, const TypesAttribute &a) {
    j = nlohmann::json{
        {"id", a.id},
        {"sortOrder", a.sortOrder},
        {"type", a.type},
        {"attribute", a.attribute}
    };
}

} // namespace dto
} // namespace Lightspeed

#endif