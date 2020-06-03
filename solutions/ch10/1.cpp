// 10-1. Your car company has completed work on a service that detects speed limits based on signage it
//       observes on the side of the road. The speed-limit-detection team will publish objects of the
//       following type to the event bus periodically: (see struct SpeedLimitDetected).
//       The service bus has been extended to incorporate this new type: (see struct IServiceBus)
//       Update the service with the new interface and make sure the tests still pass.
#include "hippomocks.h"
#include <functional>

struct SpeedLimitDetected {
  unsigned short speed_mps;
};

using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;
using SpeedLimitCallback = std::function<void(const SpeedLimitDetected&)>;

struct IServiceBus {
    virtual ~IServiceBus() = default;
    virtual void publish(const BrakeCommand&) = 0;
    virtual void subscribe(SpeedUpdateCallback) = 0;
    virtual void subscribe(CarDetectedCallback) = 0;
    virtual void subscribe(SpeedLimitCallback) = 0;
};
