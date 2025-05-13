#ifndef LIGHTSPEED_ENDPOINTS_ACCOUNT_H
#define LIGHTSPEED_ENDPOINTS_ACCOUNT_H

// Forward-declare API and include DTO definition
class LightspeedApi;
#include "../dtos/Account.h"

namespace Lightspeed {
namespace endpoints {

class AccountEndpoint {
public:
  AccountEndpoint(LightspeedApi &api);
  Lightspeed::dto::Account get();
private:
  LightspeedApi &api_;
};

} // namespace endpoints
} // namespace Lightspeed

#endif // LIGHTSPEED_ENDPOINTS_ACCOUNT_H
