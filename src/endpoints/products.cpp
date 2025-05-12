// Relative paths for library files
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

int ProductsEndpoint::getCount() {
  std::string countJson = api_.performGetRequest("products/count.json");
  auto json = nlohmann::json::parse(countJson);
  return json.at("count").get<int>();
}

Lightspeed::dto::Product ProductsEndpoint::get(int id) {
  std::string productJson = api_.performGetRequest("products/" + std::to_string(id) + ".json");
  auto json = nlohmann::json::parse(productJson);
  return json.at("product").get<Lightspeed::dto::Product>();
}

Lightspeed::dto::Product ProductsEndpoint::create(Lightspeed::dto::Product product) {
  std::string productJson = api_.performPostRequest("products.json", product.toJson());
  auto json = nlohmann::json::parse(productJson);
  return json.at("product").get<Lightspeed::dto::Product>();
}