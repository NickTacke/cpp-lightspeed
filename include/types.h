#ifndef LIGHTSPEED_TYPES_H
#define LIGHTSPEED_TYPES_H

#include "nlohmann/json.hpp"

namespace Lightspeed {

// For responses like {"count": 123}
struct CountResponse {
    int count;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CountResponse, count)
};

// You can add other common simple types here as needed.

} // namespace Lightspeed

#endif // LIGHTSPEED_TYPES_H 