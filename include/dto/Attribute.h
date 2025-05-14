#ifndef LIGHTSPEED_DTOS_ATTRIBUTE_H
#define LIGHTSPEED_DTOS_ATTRIBUTE_H

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

struct Attribute {
    int id;
    std::string title;
    std::string defaultValue;
};

inline void from_json(const nlohmann::json &j, Attribute &a) {
    j.at("id").get_to(a.id);
    j.at("title").get_to(a.title);
    j.at("defaultValue").get_to(a.defaultValue);
}

inline void to_json(nlohmann::json &j, const Attribute &a) {
    j = nlohmann::json{
        {"id", a.id},
        {"title", a.title},
        {"defaultValue", a.defaultValue}
    };
}

} // namespace dto
} // namespace Lightspeed

#endif