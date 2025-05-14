#ifndef LIGHTSPEED_DTOS_TYPE_H
#define LIGHTSPEED_DTOS_TYPE_H

#include <nlohmann/json.hpp>
#include <string>

#include "Resource.h"
#include "TypesAttribute.h"

namespace Lightspeed {
namespace dto {

struct Type {
    int id;
    std::string title;
    Resource<TypesAttribute> attributes;
};

inline void from_json(const nlohmann::json &j, Type &t) {
    j.at("id").get_to(t.id);
    j.at("title").get_to(t.title);
    j.at("attributes").get_to(t.attributes);
}

} // namespace dto
} // namespace Lightspeed

#endif