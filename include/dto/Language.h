#ifndef LIGHTSPEED_DTOS_LANGUAGE_H
#define LIGHTSPEED_DTOS_LANGUAGE_H

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

struct Language {
    int id;
    bool isActive;
    bool isDefault;
    std::string code;
    std::string locale;
    std::string title;
};

inline void from_json(const nlohmann::json &j, Language &l) {
    j.at("id").get_to(l.id);
    j.at("isActive").get_to(l.isActive);
    j.at("isDefault").get_to(l.isDefault);
    j.at("code").get_to(l.code);
    j.at("locale").get_to(l.locale);
    j.at("title").get_to(l.title);
}

inline void to_json(nlohmann::json &j, const Language &l) {
    j = nlohmann::json{
        {"id", l.id},
        {"isActive", l.isActive},
        {"isDefault", l.isDefault},
        {"code", l.code},
        {"locale", l.locale},
        {"title", l.title}
    };
}

} // namespace dto
} // namespace Lightspeed

#endif