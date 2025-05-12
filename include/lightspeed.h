#ifndef LIGHTSPEED_H
#define LIGHTSPEED_H

#include <string>
#include <vector>

// Endpoint includes

class LightspeedApi {
public:
  enum class Cluster { EU1, US1 };

  LightspeedApi(const std::string &apiKey, const std::string &apiSecret,
                Cluster cluster, const std::string &language = "en");
  LightspeedApi(const std::string &apiKey, const std::string &apiSecret,
                const std::string &customBaseUrl);

private:
  std::string apiKey_;
  std::string apiSecret_;
  std::string baseUrlHost_;
  std::string baseUrlPath_;

  std::string getFullPath(const std::string &endpoint) const;
  std::string performRequest(
      const std::string &method, const std::string &endpoint,
      const std::string &body,
      const std::vector<std::pair<std::string, std::string>> &queryParams);
};

#endif