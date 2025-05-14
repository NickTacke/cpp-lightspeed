#ifndef LIGHTSPEED_DTOS_ACCOUNT_METAFIELDS_H
#define LIGHTSPEED_DTOS_ACCOUNT_METAFIELDS_H

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Lightspeed {
namespace dto {

struct AccountMetafield {
public:
  int id;
  std::string createdAt;
  std::string updatedAt;
  std::string key;
  std::string value;
};

// Deserializer for single metafield entries
inline void from_json(const nlohmann::json &j, AccountMetafield &f) {
  j.at("id").get_to(f.id);
  j.at("createdAt").get_to(f.createdAt);
  j.at("updatedAt").get_to(f.updatedAt);
  j.at("key").get_to(f.key);
  j.at("value").get_to(f.value);
}

inline void to_json(nlohmann::json &j, const AccountMetafield &f) {
  j = nlohmann::json{
    {"id", f.id},
    {"createdAt", f.createdAt},
    {"updatedAt", f.updatedAt},
    {"key", f.key},
    {"value", f.value}
  };
}

} // namespace dto
} // namespace Lightspeed

#endif