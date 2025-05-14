#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "lightspeed.h"
#include "httplib/httplib.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>

namespace {
// Helper to parse a full URL into scheme, host and base path
struct ParsedUrl {
  std::string scheme;
  std::string host;
  std::string path;
};

ParsedUrl parse_url(const std::string &url_string) {
  std::regex url_regex(R"(([^:]+)://([^/]+)(/.*)?)");
  std::smatch match;
  // Check if the URL matches the expected format
  if (std::regex_match(url_string, match, url_regex)) {
    return {match[1].str(), match[2].str(),
            match[3].matched ? match[3].str() : "/"};
  }
  throw std::invalid_argument("Invalid URL: " + url_string);
}

// Helper to build query parameter string
std::string build_query_params(
    const std::vector<std::pair<std::string, std::string>> &queryParams) {
  // If no query params, return empty string
  if (queryParams.empty()) {
    return "";
  }

  // Build query string
  std::string query_string = "?";
  for (size_t i = 0; i < queryParams.size(); i++) {
    query_string += queryParams[i].first + "=" + queryParams[i].second;
    if (i < queryParams.size() - 1) {
      query_string += "&";
    }
  }
  return query_string;
}

// Helper to parse rate limit header strings like "X/Y/Z" into a vector of integers
static std::vector<int> parse_rate_limit_values(const std::string& header_value) {
    std::vector<int> values;
    if (header_value.empty()) {
        return values;
    }
    std::stringstream ss(header_value);
    std::string item;
    while (std::getline(ss, item, '/')) {
        try {
            if (!item.empty()) { // Ensure item is not empty before trying to convert
                values.push_back(std::stoi(item));
            }
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Rate limit parsing warning: Invalid number '" << item << "' in header value '" << header_value << "'. " << ia.what() << std::endl;
        } catch (const std::out_of_range& oor) {
            std::cerr << "Rate limit parsing warning: Number '" << item << "' out of range in header value '" << header_value << "'. " << oor.what() << std::endl;
        }
    }
    return values;
}

} // namespace

LightspeedApi::LightspeedApi(const std::string &apiKey,
                             const std::string &apiSecret, Cluster cluster,
                             const std::string &language)
    : apiKey_(apiKey), apiSecret_(apiSecret), account(*this), products(*this) {
  std::string clusterBaseHost;
  switch (cluster) {
  case Cluster::EU1:
    clusterBaseHost = "api.webshopapp.com";
    break;
  case Cluster::US1:
    clusterBaseHost = "api.shoplightspeed.com";
    break;
  default:
    throw std::runtime_error("Invalid cluster specified");
  }
  baseUrlHost_ = clusterBaseHost;
  baseUrlPath_ = "/" + language + "/";
}

LightspeedApi::LightspeedApi(const std::string &apiKey,
                             const std::string &apiSecret,
                             const std::string &customBaseUrl)
    : apiKey_(apiKey), apiSecret_(apiSecret), account(*this), products(*this) {
  if (customBaseUrl.empty()) {
    throw std::invalid_argument("Custom base URL cannot be empty");
  }
  ParsedUrl parsed = parse_url(customBaseUrl);
  baseUrlHost_ = parsed.host;
  baseUrlPath_ = parsed.path;
  // Ensure the path ends with a slash
  if (baseUrlPath_.back() != '/') {
    baseUrlPath_ += '/';
  }
}

std::string LightspeedApi::getFullPath(const std::string &endpoint) const {
  std::string effective_endpoint = endpoint;
  // Remove leading slash if present
  if (!endpoint.empty() && endpoint.front() == '/') {
    effective_endpoint = endpoint.substr(1);
  }
  return baseUrlPath_ + effective_endpoint;
}

std::string LightspeedApi::performRequest(
    const std::string &method, const std::string &endpoint,
    const std::string &body,
    const std::vector<std::pair<std::string, std::string>> &queryParams) {
  // Initialize the httplib client
  httplib::SSLClient client(baseUrlHost_);
  client.set_default_headers(
      {{"Authorization", "Basic " + httplib::detail::base64_encode(
                                        apiKey_ + ":" + apiSecret_)}});
  client.set_connection_timeout(10, 0);
  client.set_read_timeout(30, 0);
  client.enable_server_certificate_verification(true);

  // Build the full path with query parameters
  std::string full_path_with_query =
      getFullPath(endpoint) + build_query_params(queryParams);

  // Perform the request
  httplib::Result result;
  if (method == "GET") {
    result = client.Get(full_path_with_query.c_str());
  } else if (method == "POST") {
    result =
        client.Post(full_path_with_query.c_str(), body, "application/json");
  } else if (method == "PUT") {
    result = client.Put(full_path_with_query.c_str(), body, "application/json");
  } else if (method == "DELETE") {
    result = client.Delete(full_path_with_query.c_str());
  } else {
    throw std::invalid_argument("Unsupported HTTP method: " + method);
  }

  // Check if the request failed
  if (!result) {
    auto err = result.error();
    std::string error_msg = httplib::to_string(err);
    std::cerr << "HTTP Request failed: " << error_msg << std::endl;
    throw std::runtime_error("Request failed: " + error_msg);
  }

  // Check the response code
  if (result->status >= 200 && result->status < 300) {
    // Print response headers
    std::cout << "Response headers:" << std::endl;
    for (const auto &header : result->headers) {
      std::cout << header.first << ": " << header.second << std::endl;
    }
    
    // Parse and store rate limit information
    std::string rate_limit_limit_str = result->get_header_value("X-RateLimit-Limit");
    std::string rate_limit_remaining_str = result->get_header_value("X-RateLimit-Remaining");
    std::string rate_limit_reset_str = result->get_header_value("X-RateLimit-Reset");

    std::vector<int> limits = parse_rate_limit_values(rate_limit_limit_str);
    std::vector<int> remaining_values = parse_rate_limit_values(rate_limit_remaining_str);
    std::vector<int> reset_values = parse_rate_limit_values(rate_limit_reset_str);

    // Populate AccountRateLimits structure
    // Assuming the order in headers is 5min, 1hour, 1day
    if (limits.size() >= 1) this->lastRateLimitInfo_.limit5Min.limit = limits[0];
    if (limits.size() >= 2) this->lastRateLimitInfo_.limitHour.limit = limits[1];
    if (limits.size() >= 3) this->lastRateLimitInfo_.limitDay.limit = limits[2];

    if (remaining_values.size() >= 1) this->lastRateLimitInfo_.limit5Min.remaining = remaining_values[0];
    if (remaining_values.size() >= 2) this->lastRateLimitInfo_.limitHour.remaining = remaining_values[1];
    if (remaining_values.size() >= 3) this->lastRateLimitInfo_.limitDay.remaining = remaining_values[2];

    if (reset_values.size() >= 1) this->lastRateLimitInfo_.limit5Min.reset = reset_values[0];
    if (reset_values.size() >= 2) this->lastRateLimitInfo_.limitHour.reset = reset_values[1];
    if (reset_values.size() >= 3) this->lastRateLimitInfo_.limitDay.reset = reset_values[2];

    return result->body;
  } else {
    std::cerr << "Unsupported response code: " << result->status << std::endl;
    throw std::runtime_error("Request failed: " + result->body);
  }
}

std::string LightspeedApi::performGetRequest(
    const std::string &endpoint,
    const std::vector<std::pair<std::string, std::string>> &queryParams) {
  return performRequest("GET", endpoint, "", queryParams);
}

std::string LightspeedApi::performPostRequest(
    const std::string &endpoint, const std::string &body,
    const std::vector<std::pair<std::string, std::string>> &queryParams) {
  return performRequest("POST", endpoint, body, queryParams);
}

std::string LightspeedApi::performPutRequest(
    const std::string &endpoint, const std::string &body,
    const std::vector<std::pair<std::string, std::string>> &queryParams) {
  return performRequest("PUT", endpoint, body, queryParams);
}

std::string LightspeedApi::performDeleteRequest(
    const std::string &endpoint,
    const std::vector<std::pair<std::string, std::string>> &queryParams) {
  return performRequest("DELETE", endpoint, "", queryParams);
}