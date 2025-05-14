#ifndef LIGHTSPEED_DTOS_ACCOUNT_H
#define LIGHTSPEED_DTOS_ACCOUNT_H

#include "./Resource.h" // Relative path
#include "./AccountMetafields.h"
#include "./AccountPermissions.h"
#include "./AccountRateLimits.h"

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

class Account {
public:
  int id;
  int appId;
  std::string apiKey;
  Resource<std::vector<AccountMetafield>> metafields;
  Resource<AccountPermissions> permissions;
  Resource<AccountRateLimits> rateLimits;
};

inline void from_json(const nlohmann::json &j, Account &a) {
  j.at("id").get_to(a.id);
  j.at("appId").get_to(a.appId);
  j.at("apiKey").get_to(a.apiKey);
  j.at("metafields").get_to(a.metafields);
  j.at("permissions").get_to(a.permissions);
  j.at("ratelimit").get_to(a.rateLimits);
}

inline void to_json(nlohmann::json& j, const Account &a) {
  j = nlohmann::json{
    {"id", a.id},
    {"appId", a.appId},
    {"apiKey", a.apiKey},
    {"metafields", a.metafields},
    {"permissions", a.permissions},
    {"ratelimit", a.rateLimits}
  };
}

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTOS_ACCOUNT_H