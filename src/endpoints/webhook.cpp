#include "endpoints/webhook.h"
#include "lightspeed.h"
#include "nlohmann/json.hpp"

namespace Lightspeed {
namespace endpoints {

WebhookEndpoint::WebhookEndpoint(LightspeedApi& api_client)
    : apiClient_(api_client) {}

std::vector<dto::Webhook> WebhookEndpoint::getWebhooks(const std::vector<std::pair<std::string, std::string>>& queryParams) {
    std::string response = apiClient_.performGetRequest("/webhooks.json", queryParams);
    nlohmann::json j = nlohmann::json::parse(response);
    return j.at("webhooks").get<std::vector<dto::Webhook>>();
}

CountResponse WebhookEndpoint::getWebhooksCount(const std::vector<std::pair<std::string, std::string>>& queryParams) {
    std::string response = apiClient_.performGetRequest("/webhooks/count.json", queryParams);
    nlohmann::json j = nlohmann::json::parse(response);
    return j.get<CountResponse>();
}

std::optional<dto::Webhook> WebhookEndpoint::getWebhook(int webhookId) {
    try {
        std::string response = apiClient_.performGetRequest("/webhooks/" + std::to_string(webhookId) + ".json");
        nlohmann::json j = nlohmann::json::parse(response);
        return j.at("webhook").get<dto::Webhook>();
    } catch (const std::exception& e) {
        // Handle cases like 404 Not Found or parsing errors
        std::cerr << "Error getting webhook " << webhookId << ": " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<dto::Webhook> WebhookEndpoint::createWebhook(const dto::Webhook& webhookData) {
    nlohmann::json payloadBody;
    // Construct the payload carefully based on API requirements
    if (webhookData.isActive.has_value()) payloadBody["isActive"] = webhookData.isActive.value();
    if (webhookData.itemGroup.has_value()) payloadBody["itemGroup"] = webhookData.itemGroup.value();
    if (webhookData.itemAction.has_value()) payloadBody["itemAction"] = webhookData.itemAction.value();
    if (webhookData.languageCode.has_value()) payloadBody["language"] = webhookData.languageCode.value(); // API expects language string here
    if (webhookData.format.has_value()) payloadBody["format"] = webhookData.format.value();
    if (webhookData.address.has_value()) payloadBody["address"] = webhookData.address.value();

    nlohmann::json payload;
    payload["webhook"] = payloadBody;

    try {
        std::string response = apiClient_.performPostRequest("/webhooks.json", payload.dump());
        nlohmann::json jResponse = nlohmann::json::parse(response);
        return jResponse.at("webhook").get<dto::Webhook>();
    } catch (const std::exception& e) {
        std::cerr << "Error creating webhook: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<dto::Webhook> WebhookEndpoint::updateWebhook(int webhookId, const dto::Webhook& webhookData) {
    nlohmann::json payloadBody;
    // Construct the payload, only include fields to be updated
    if (webhookData.isActive.has_value()) payloadBody["isActive"] = webhookData.isActive.value();
    if (webhookData.itemGroup.has_value()) payloadBody["itemGroup"] = webhookData.itemGroup.value();
    if (webhookData.itemAction.has_value()) payloadBody["itemAction"] = webhookData.itemAction.value();
    // Language cannot be updated via PUT according to docs, only on POST.
    // If it were allowed, it would be: if (webhookData.languageCode.has_value()) payloadBody["language"] = webhookData.languageCode.value();
    if (webhookData.format.has_value()) payloadBody["format"] = webhookData.format.value();
    if (webhookData.address.has_value()) payloadBody["address"] = webhookData.address.value();

    if (payloadBody.empty()) {
        // Nothing to update
        return getWebhook(webhookId); // Or handle as an error/no-op
    }

    nlohmann::json payload;
    payload["webhook"] = payloadBody;

    try {
        std::string response = apiClient_.performPutRequest("/webhooks/" + std::to_string(webhookId) + ".json", payload.dump());
        nlohmann::json jResponse = nlohmann::json::parse(response);
        return jResponse.at("webhook").get<dto::Webhook>();
    } catch (const std::exception& e) {
        std::cerr << "Error updating webhook " << webhookId << ": " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool WebhookEndpoint::deleteWebhook(int webhookId) {
    try {
        apiClient_.performDeleteRequest("/webhooks/" + std::to_string(webhookId) + ".json");
        // DELETE typically returns 204 No Content on success
        // The performDeleteRequest should throw on failure, so if we reach here, it's a success.
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error deleting webhook " << webhookId << ": " << e.what() << std::endl;
        return false;
    }
}

} // namespace endpoints
} // namespace Lightspeed 