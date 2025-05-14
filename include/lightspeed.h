#ifndef LIGHTSPEED_H
#define LIGHTSPEED_H

#include <iostream>
#include <string>
#include <vector>

// Endpoint includes
#include "endpoints/account.h"
#include "endpoints/products.h"
#include "endpoints/webhook.h"

class LightspeedApi {
public:
  enum class Cluster { EU1, US1 };

  LightspeedApi(const std::string &apiKey, const std::string &apiSecret,
                Cluster cluster, const std::string &language = "en");
  LightspeedApi(const std::string &apiKey, const std::string &apiSecret,
                const std::string &customBaseUrl);

  // Method for GET requests
  std::string performGetRequest(
      const std::string &endpoint,
      const std::vector<std::pair<std::string, std::string>> &queryParams = {});

  // Method for POST requests
  std::string performPostRequest(
      const std::string &endpoint, const std::string &body,
      const std::vector<std::pair<std::string, std::string>> &queryParams = {});

  // Method for PUT requests
  std::string performPutRequest(
      const std::string &endpoint, const std::string &body,
      const std::vector<std::pair<std::string, std::string>> &queryParams = {});

  // Method for DELETE requests
  std::string performDeleteRequest(
      const std::string &endpoint,
      const std::vector<std::pair<std::string, std::string>> &queryParams = {});

  // Endpoints
  Lightspeed::endpoints::AccountEndpoint account;
  Lightspeed::endpoints::ProductsEndpoint products;
  Lightspeed::endpoints::WebhookEndpoint webhooks;

  // Expose templated resource fetcher publicly
  template<typename T>
  T getResource(const Lightspeed::dto::Resource<T>& res);

private:
  std::string apiKey_;
  std::string apiSecret_;
  std::string baseUrlHost_;
  std::string baseUrlPath_;

  // Helper to construct the full path for a request
  std::string getFullPath(const std::string &endpoint) const;

  // Internal generic request performer
  std::string performRequest(
      const std::string &method, const std::string &endpoint,
      const std::string &body,
      const std::vector<std::pair<std::string, std::string>> &queryParams);
};

#endif

// Inline definition of templated getResource (must live in header)
#include <nlohmann/json.hpp>
template<typename T>
T LightspeedApi::getResource(const Lightspeed::dto::Resource<T>& res) {
  auto body = performGetRequest(res.url + ".json");
  nlohmann::json j = nlohmann::json::parse(body);
  if (j.size() == 1 && (j.begin().value().is_object() || j.begin().value().is_array()))
    return j.begin().value().template get<T>();
  return j.template get<T>();
}