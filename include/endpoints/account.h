#ifndef LIGHTSPEED_ENDPOINTS_ACCOUNT_H
#define LIGHTSPEED_ENDPOINTS_ACCOUNT_H

#include "../dtos/Account.h"

class LightspeedApi; // Forward declaration

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
