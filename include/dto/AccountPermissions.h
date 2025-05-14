#ifndef LIGHTSPEED_DTOS_ACCOUNT_PERMISSIONS_H
#define LIGHTSPEED_DTOS_ACCOUNT_PERMISSIONS_H

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Lightspeed {
namespace dto {

struct Permission {
    bool read;
    bool write;
};

inline void from_json(const nlohmann::json &j, Permission &p) {
  j.at("read").get_to(p.read);
  j.at("write").get_to(p.write);
}

inline void to_json(nlohmann::json &j, const Permission &p) {
  j = nlohmann::json{
    {"read", p.read ? true : false},
    {"write", p.write ? true : false}
  };
}

struct AccountPermissions {
public:
  Permission content;
  Permission products;
  Permission customers;
  Permission orders;
  Permission settings;
  Permission tracking;
};

// Deserializer for single metafield entries
inline void from_json(const nlohmann::json &j, AccountPermissions &f) {
  j.at("content").get_to(f.content);
  j.at("products").get_to(f.products);
  j.at("customers").get_to(f.customers);
  j.at("orders").get_to(f.orders);
  j.at("settings").get_to(f.settings);
  j.at("tracking").get_to(f.tracking);
}

inline void to_json(nlohmann::json &j, const AccountPermissions &f) {
  j = nlohmann::json{
    {"content", f.content},
    {"products", f.products},
    {"customers", f.customers},
    {"orders", f.orders},
    {"settings", f.settings},
    {"tracking", f.tracking}
  };
}

} // namespace dto
} // namespace Lightspeed

#endif