#include "../../include/endpoints/products.h"
#include "../../include/lightspeed.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

ProductsEndpoint::ProductsEndpoint(LightspeedApi &api) : api_(api) {}

std::string ProductsEndpoint::getPage(int page) {
  std::vector<std::pair<std::string, std::string>> queryParams = {
      {"page", std::to_string(page)}, {"limit", "250"}};

  std::string pageJson = api_.performGetRequest("products.json", queryParams);
  return pageJson;
}