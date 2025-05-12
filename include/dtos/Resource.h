#ifndef LIGHTSPEED_DTOS_RESOURCE_H
#define LIGHTSPEED_DTOS_RESOURCE_H

#include <nlohmann/json.hpp>
#include <string>

namespace Lightspeed {
namespace dto {

class Resource {
public:
  int id;
  std::string url;
  std::string link;

  std::string toJson() const {
    nlohmann::json wrapper;
    wrapper["resource"] = {
      {"id", id},
      {"url", url},
      {"link", link}
    };
    return wrapper.dump();
  }
};

inline void from_json(const nlohmann::json &j, Resource &r) {
  j.at("id").get_to(r.id);
  j.at("url").get_to(r.url);
  j.at("link").get_to(r.link);
}

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTOS_RESOURCE_H
