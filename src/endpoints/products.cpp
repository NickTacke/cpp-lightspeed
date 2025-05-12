#include "../../include/endpoints/products.h"
#include "../../include/dtos/Product.h"
#include "../../include/lightspeed.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

ProductsEndpoint::ProductsEndpoint(LightspeedApi &api) : api_(api) {}

std::vector<Lightspeed::dto::Product> ProductsEndpoint::getPage(int page) {
  std::vector<std::pair<std::string, std::string>> queryParams = {
      {"page", std::to_string(page)}, {"limit", "250"}};

  std::string pageJson = api_.performGetRequest("products.json", queryParams);
  // Deserialize products array directly using from_json
  auto json = nlohmann::json::parse(pageJson);
  return json.at("products").get<std::vector<Lightspeed::dto::Product>>();
}