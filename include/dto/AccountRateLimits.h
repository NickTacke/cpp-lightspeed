#ifndef LIGHTSPEED_DTOS_ACCOUNT_RATELIMITS_H
#define LIGHTSPEED_DTOS_ACCOUNT_RATELIMITS_H

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Lightspeed {
namespace dto {

struct RateLimit {
    int limit;
    int remaining;
    int reset;
    std::string resetTime;
};

inline void from_json(const nlohmann::json &j, RateLimit &r) {
  j.at("limit").get_to(r.limit);
  j.at("remaining").get_to(r.remaining);
  j.at("reset").get_to(r.reset);
  j.at("resetTime").get_to(r.resetTime);
}

inline void to_json(nlohmann::json &j, const RateLimit &r) {
  j = nlohmann::json{
    {"limit", r.limit},
    {"remaining", r.remaining},
    {"reset", r.reset},
    {"resetTime", r.resetTime}
  };
}

struct AccountRateLimits {
public:
  RateLimit limit5Min;
  RateLimit limitHour;
  RateLimit limitDay;
};

// Deserializer for single metafield entries
inline void from_json(const nlohmann::json &j, AccountRateLimits &f) {
  j.at("limit5Min").get_to(f.limit5Min);
  j.at("limitHour").get_to(f.limitHour);
  j.at("limitDay").get_to(f.limitDay);
}

inline void to_json(nlohmann::json &j, const AccountRateLimits &f) {
  j = nlohmann::json{
    {"limit5Min", f.limit5Min},
    {"limitHour", f.limitHour},
    {"limitDay", f.limitDay}
  };
}

} // namespace dto
} // namespace Lightspeed

#endif