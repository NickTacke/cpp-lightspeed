#ifndef LIGHTSPEED_ENDPOINT_WEBHOOK_H
#define LIGHTSPEED_ENDPOINT_WEBHOOK_H

#include <string>
#include <vector>
#include <optional>
#include "../dto/webhook.h"
#include "../types.h"

// Forward declare LightspeedApi to avoid circular dependency
class LightspeedApi;

namespace Lightspeed {
namespace endpoints {

class WebhookEndpoint {
public:
    explicit WebhookEndpoint(LightspeedApi& api_client);

    // GET /webhooks.json
    std::vector<dto::Webhook> getWebhooks(const std::vector<std::pair<std::string, std::string>>& queryParams = {});

    // GET /webhooks/count.json
    CountResponse getWebhooksCount(const std::vector<std::pair<std::string, std::string>>& queryParams = {});

    // GET /webhooks/{webhook_id}.json
    std::optional<dto::Webhook> getWebhook(int webhookId);

    // POST /webhooks.json
    std::optional<dto::Webhook> createWebhook(const dto::Webhook& webhookData);

    // PUT /webhooks/{webhook_id}.json
    std::optional<dto::Webhook> updateWebhook(int webhookId, const dto::Webhook& webhookData);

    // DELETE /webhooks/{webhook_id}.json
    bool deleteWebhook(int webhookId);

private:
    LightspeedApi& apiClient_;
};

} // namespace endpoints
} // namespace Lightspeed

#endif // LIGHTSPEED_ENDPOINT_WEBHOOK_H 