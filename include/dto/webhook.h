#ifndef LIGHTSPEED_DTO_WEBHOOK_H
#define LIGHTSPEED_DTO_WEBHOOK_H

#include <string>
#include <optional>
#include "nlohmann/json.hpp"

namespace Lightspeed {
namespace dto {

struct WebhookLanguage {
    std::optional<int> id;
    std::optional<std::string> code;
    std::optional<std::string> locale;
    std::optional<std::string> title;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(WebhookLanguage, id, code, locale, title)
};

struct Webhook {
    std::optional<int> id;
    std::optional<std::string> createdAt;
    std::optional<std::string> updatedAt;
    std::optional<bool> isActive;
    std::optional<std::string> itemGroup;
    std::optional<std::string> itemAction;
    std::optional<WebhookLanguage> language; // Used in response
    std::optional<std::string> languageCode; // Used in request (e.g., "us")
    std::optional<std::string> format;
    std::optional<std::string> address;

    // For responses that wrap the object, e.g. {"webhook": {...}}
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Webhook, id, createdAt, updatedAt, isActive, itemGroup, itemAction, language, format, address)

    // Custom deserialization to handle languageCode for requests if needed,
    // and the nested language object for responses.
    // For simplicity in this example, we'll primarily use languageCode for requests
    // and expect the full language object in responses.
    // When creating/updating, only languageCode might be set by the user of the library.
};

// For requests, the payload might be slightly different, especially for language.
// We'll handle this in the endpoint methods. For example, when creating a webhook:
// {
//   "webhook": {
//     "isActive": true,
//     "itemGroup": "products",
//     "itemAction": "*",
//     "language": "us", // Note: API docs show this as a string for POST
//     "format": "xml",
//     "address": "https://requestb.in/12345"
//   }
// }
// The NLOHMANN_DEFINE_TYPE_INTRUSIVE should handle most cases, but we need to be mindful of this.

} // namespace dto
} // namespace Lightspeed

#endif // LIGHTSPEED_DTO_WEBHOOK_H 