#ifndef LIGHTSPEED_DTOS_PRODUCT_H
#define LIGHTSPEED_DTOS_PRODUCT_H

#include <nlohmann/json.hpp>
#include <string>

#include "Resource.h"
#include "Variant.h"

namespace Lightspeed {
namespace dto {

struct Product {
  int id;
  std::string createdAt;
  std::string updatedAt;
  bool isVisible;
  std::string visibility;
  std::string url;
  std::string title;
  std::string fulltitle;
  std::string description;
  std::string content;
  Resource<std::vector<Variant>> variants;
};

inline void from_json(const nlohmann::json &j, Product &p) {
  j.at("id").get_to(p.id);
  j.at("createdAt").get_to(p.createdAt);
  j.at("updatedAt").get_to(p.updatedAt);
  j.at("isVisible").get_to(p.isVisible);
  j.at("visibility").get_to(p.visibility);
  j.at("url").get_to(p.url);
  j.at("title").get_to(p.title);
  j.at("fulltitle").get_to(p.fulltitle);
  j.at("description").get_to(p.description);
  j.at("content").get_to(p.content);
  j.at("variants").get_to(p.variants);
}

inline void to_json(nlohmann::json &j, const Product &p) {
  j = nlohmann::json{
    {"id", p.id},
    {"createdAt", p.createdAt},
    {"updatedAt", p.updatedAt},
    {"isVisible", p.isVisible},
    {"visibility", p.visibility},
    {"url", p.url},
    {"title", p.title},
    {"fulltitle", p.fulltitle},
    {"description", p.description},
    {"content", p.content},
    {"variants", p.variants}
  };
}

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTOS_PRODUCT_H