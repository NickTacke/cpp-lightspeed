#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "lightspeed.h"

LightspeedApi::LightspeedApi(const std::string &apiKey,
                             const std::string &apiSecret, Cluster cluster,
                             const std::string &language)
    : apiKey_(apiKey), apiSecret_(apiSecret) {
  // TODO: Implement
}

LightspeedApi::LightspeedApi(const std::string &apiKey,
                             const std::string &apiSecret,
                             const std::string &customBaseUrl)
    : apiKey_(apiKey), apiSecret_(apiSecret) {
  // TODO: Implement
}

std::string LightspeedApi::getFullPath(const std::string &endpoint) const {
  std::string effective_endpoint = endpoint;
  // Remove leading slash if present
  if (!endpoint.empty() && endpoint.front() == '/') {
    effective_endpoint = endpoint.substr(1);
  }
  return baseUrlPath_ + effective_endpoint;
}

std::string LightspeedApi::performRequest() {
  // TODO: Implement
}