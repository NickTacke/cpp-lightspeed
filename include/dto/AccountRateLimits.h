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

    std::string toJson() const {
      nlohmann::json wrapper;
      wrapper = {
        {"limit", limit},
        {"remaining", remaining},
        {"reset", reset},
        {"resetTime", resetTime}
      };
      return wrapper.dump();
    }
};

inline void from_json(const nlohmann::json &j, RateLimit &r) {
  j.at("limit").get_to(r.limit);
  j.at("remaining").get_to(r.remaining);
  j.at("reset").get_to(r.reset);
  j.at("resetTime").get_to(r.resetTime);
}

struct AccountRateLimits {
public:
  RateLimit limit5Min;
  RateLimit limitHour;
  RateLimit limitDay;

  std::string toJson() const {
    nlohmann::json wrapper;
    wrapper["accountRatelimit"] = {
      {"limit5Min", limit5Min.toJson()},
      {"limitHour", limitHour.toJson()},
      {"limitDay", limitDay.toJson()}
    };
    return wrapper.dump();
  }
};

// Deserializer for single metafield entries
inline void from_json(const nlohmann::json &j, AccountRateLimits &f) {
  j.at("limit5Min").get_to(f.limit5Min);
  j.at("limitHour").get_to(f.limitHour);
  j.at("limitDay").get_to(f.limitDay);
}

} // namespace dto
} // namespace Lightspeed

#endif