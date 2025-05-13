#ifndef LIGHTSPEED_DTOS_ACCOUNT_H
#define LIGHTSPEED_DTOS_ACCOUNT_H

#include "./Resource.h" // Relative path
#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

class Account {
public:
  int id;
  int appId;
  std::string apiKey;
  Lightspeed::dto::Resource signout;
  Lightspeed::dto::Resource permissions;
  Lightspeed::dto::Resource ratelimit;
  Lightspeed::dto::Resource metafields;

  std::string toJson() const {
    nlohmann::json wrapper;
    wrapper["account"] = {
      {"id", id},
      {"appId", appId},
      {"apiKey", apiKey},
    };
    return wrapper.dump();
  }
};

inline void from_json(const nlohmann::json &j, Account &a) {
  j.at("id").get_to(a.id);
  j.at("appId").get_to(a.appId);
  j.at("apiKey").get_to(a.apiKey);
  j.at("signout").get_to(a.signout);
  j.at("permissions").get_to(a.permissions);
  j.at("ratelimit").get_to(a.ratelimit);
  j.at("metafields").get_to(a.metafields);
}

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTOS_ACCOUNT_H