#ifndef LIGHTSPEED_DTOS_COUNT_H
#define LIGHTSPEED_DTOS_COUNT_H

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

struct Count {
    int count;
};

inline void from_json(const nlohmann::json &j, Count &c) {
    j.at("count").get_to(c.count);
}

inline void to_json(nlohmann::json &j, const Count &c) {
    j = nlohmann::json{
        {"count", c.count}
    };
}

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTOS_COUNT_H
