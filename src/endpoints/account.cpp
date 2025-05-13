// Relative paths for library files
#include "../../include/lightspeed.h"
#include "../../include/endpoints/account.h"

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace endpoints {

AccountEndpoint::AccountEndpoint(LightspeedApi &api) : api_(api) {}

Lightspeed::dto::Account AccountEndpoint::get() {
  std::string accountJson = api_.performGetRequest("account.json");
  auto json = nlohmann::json::parse(accountJson);
  return json.at("account").get<Lightspeed::dto::Account>();
}

} // namespace endpoints
} // namespace Lightspeed